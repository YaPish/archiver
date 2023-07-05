#include <fstream>
#include <iomanip>
#include <filesystem>
#include <algorithm>
#include <cstring>

#include <bitset>

#include "archive.h"


void putIntToFile( std::uintmax_t value, std::fstream * file, std::uint8_t countBytes ) {
    if( countBytes > sizeof( std::uintmax_t ) || countBytes == 0 ) return;

    std::uint8_t * valueBytes = new std::uint8_t[ countBytes ];
    for( std::int8_t i = 0; i < countBytes; i++ )
        valueBytes[ i ] = static_cast< std::uint8_t >( value >> ( i * 0x8 ) );
    for( std::int8_t i = countBytes - 1; i >= 0; i-- )
        file->put( valueBytes[ i ] );

    delete[] valueBytes;
}

std::uintmax_t getIntFromFile( std::fstream * file, std::uint8_t countBytes ) {
    std::uintmax_t result = 0;
    if( countBytes > sizeof( std::uintmax_t ) ) return result;

    for( std::int8_t i = 0; i < countBytes; i++ ) {
        result |= static_cast< std::uintmax_t >( file->get() )
               << ( 0x8 * ( countBytes - i - 1 ) );
    }
    return result;
}


///////////////////////////////////////////////////////////////////////////////
//                                Properties                                 //
///////////////////////////////////////////////////////////////////////////////

std::uintmax_t Archive::m_idSize( std::filesystem::file_type type ) {
    std::uintmax_t result = 0;
    std::uintmax_t srcNameSize;
    switch( type ) {
        case std::filesystem::file_type::directory:
            srcNameSize = m_folderId;
            break;
        default:
            srcNameSize = m_fileId;
            break;
    }
    while( srcNameSize ) {
        srcNameSize = srcNameSize >> ( result ? 8 : 6 ); // reserving 2 bits //
        result++;
    }
    return result;
}


///////////////////////////////////////////////////////////////////////////////
//                             Get bitwise view                              //
///////////////////////////////////////////////////////////////////////////////

std::list< std::uintmax_t > Archive::m_bitwiseContent( std::filesystem::path contentPath ) {
    std::list< std::uintmax_t > result;
    std::uintmax_t              folderPos = 0, filePos = 0;

    // Single file and empty folder
    if( !std::filesystem::is_directory( contentPath ) ) {
        m_fileNames.push_back( contentPath.filename() );

        result.insert( result.begin(), CODE_END( CODE_FILE( m_fileId ) ) );
        return result;
    }
    if ( std::filesystem::is_empty( contentPath ) ) return result;


    for( auto & entity : std::filesystem::directory_iterator( contentPath ) ) {
        auto entityPos = result.begin();

        switch( entity.status().type() ) {
            case std::filesystem::file_type::directory:
                m_folderNames.push_back( entity.path() );

                std::advance( entityPos, folderPos );
                folderPos++;
                result.insert( entityPos, CODE_FOLDER( m_folderId++ ) );
                break;
            default:
                m_fileNames.push_back( entity.path() );

                std::advance( entityPos, folderPos + filePos );
                filePos++;
                result.insert( entityPos, CODE_FILE( m_fileId++ ) );
                break;
        }
    }

    // ???
    if( filePos || !( folderPos && filePos ) )
        result.back() = CODE_END( result.back() );
    return result;
}


std::list< std::uintmax_t > Archive::m_bitwiseCatalog() {
    m_folderId = m_fileId = 1;

    std::uintmax_t              targetFolderId;
    std::list< std::uintmax_t > result;
    std::list< std::uintmax_t > folderContent;

    auto folder = result.begin();
    folderContent = m_bitwiseContent( m_srcPath );
    result.insert( folder, folderContent.begin(), folderContent.end() );
    if( !std::filesystem::is_directory( m_srcPath ) ) return result;

    for( auto & entity : std::filesystem::recursive_directory_iterator( m_srcPath ) ) {
        if( !std::filesystem::is_directory( entity.path() ) ) continue;

        auto targetIterator = m_folderNames.begin();
        for( targetFolderId = 1; targetFolderId <= m_folderNames.size(); targetFolderId++  ) {
            if( * std::next( targetIterator, targetFolderId - 1  ) == entity.path() ) break;
        }
        targetFolderId = CODE_FOLDER( targetFolderId  );


        // Get folder content
        folderContent = m_bitwiseContent( entity.path() );
        folder        = std::find( result.begin(), result.end(), targetFolderId );

        // Insert folder content
        if( folderContent.empty() ) {
            * folder = CODE_END( * folder );
        } else {
            std::advance( folder, 1 );
            result.insert( folder, folderContent.begin(), folderContent.end() );
        }
    }

    return result;
}

std::list< std::uintmax_t > Archive::m_bitwiseNames() {
    std::list< std::uintmax_t > result;

    // folders //
    for( std::uintmax_t i = 0; i < m_folderNames.size(); i++ ) {
        // delta to next //
        result.push_back( std::next( m_folderNames.begin(), i )->filename().string().size() );

        // ascii name //
        for( char c : std::next( m_folderNames.begin(), i )->filename().string() )
            result.push_back( static_cast< std::uintmax_t >( c ) );
    }

    result.push_back( 0x0 );

    // files //
    for( std::uintmax_t i = 0; i < m_fileNames.size(); i++ ) {
        // delta to next //
        result.push_back( std::next( m_fileNames.begin(), i )->filename().string().size() );

        // ascii name //
        for( char c : std::next( m_fileNames.begin(), i )->filename().string() )
            result.push_back( static_cast< std::uintmax_t >( c ) );
    }

    result.push_back( 0x0 );

    return result;
}


///////////////////////////////////////////////////////////////////////////////
//                         Normalise bitwise view                            //
///////////////////////////////////////////////////////////////////////////////

void Archive::m_normaliseCatalog( std::list< std::uintmax_t > bitwiseView ) {
    if( m_folderNames.empty() && m_fileNames.empty() )
        return;

    std::filesystem::path flowPath = m_srcPath;
    for( std::uintmax_t i : bitwiseView ) {
        std::filesystem::file_type entityType
            = ( IS_FOLDER( i ) ? std::filesystem::file_type::directory
                               : std::filesystem::file_type::regular );

        std::filesystem::path entityName
            = ( IS_FOLDER( i ) ? *std::next( m_folderNames.begin(), GET_ID( i ) - 1 )
                               : *std::next( m_fileNames.begin(),   GET_ID( i ) - 1 ) );

        std::filesystem::path entityPath = flowPath / entityName;
        switch( entityType ) {
            case std::filesystem::file_type::directory:
                std::filesystem::create_directory( entityPath );
                break;
            default:
                *std::next( m_fileNames.begin(), GET_ID( i ) - 1 )
                    = std::filesystem::absolute( entityPath );
                std::ofstream newFile( entityPath );
                break;
        }

        if( IS_END( i )  && !IS_FOLDER( i ) )
            flowPath = flowPath.parent_path();
        else if( IS_END( i )  && IS_FOLDER( i ) )
            continue;
        else if( !IS_END( i ) && IS_FOLDER( i ) )
            flowPath = flowPath / entityName;
    }
}

void Archive::m_normaliseNames( std::list< std::uintmax_t > bitwiseView ) {
    m_folderNames.clear(); m_fileNames.clear();
    m_folderId = m_fileId = 0;
    bool folderStream = true;

    for( auto i = bitwiseView.begin(); i != bitwiseView.end(); std::advance( i, 1 ) ) {
        std::string    name;
        std::uintmax_t nameSize = * i;
        if( !nameSize ) {
            folderStream = false;
            continue;
        }

        for( ; nameSize != 0; nameSize-- ) {
            std::advance( i, 1 );
            name.push_back( static_cast< char >( * i ) );
        }

        if( folderStream ) {
            m_folderNames.push_back( static_cast< std::filesystem::path >( name ) );
            m_folderId++;
        } else {
            m_fileNames.push_back( static_cast< std::filesystem::path >( name ) );
            m_fileId++;
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//                              Pack Archive file                            //
///////////////////////////////////////////////////////////////////////////////

#define BUFFER_SIZE 1048576

void Archive::m_packSignature( void ) {
    m_archiveFile.write( ARCHIVE_FLAG, sizeof( ARCHIVE_FLAG ) - 1 );
}

void Archive::m_packData( void ) {
    std::list< std::uintmax_t > bitwiseCatalog = m_bitwiseCatalog();
    std::list< std::uintmax_t > bitwiseNames   = m_bitwiseNames();

    std::uintmax_t folderIdSize = m_idSize( std::filesystem::file_type::directory );
    std::uintmax_t fileIdSize   = m_idSize( std::filesystem::file_type::regular );

    std::uint8_t  bitwiseIdSize = ( static_cast< std::uint8_t >( folderIdSize ) << 4 )
                                | ( static_cast< std::uint8_t >( fileIdSize )   &  0xF );


    // Names
    auto entity = bitwiseNames.begin();
    for( ; entity != bitwiseNames.end(); std::advance( entity, 1 ) )
        m_archiveFile.put( * entity );

    // Entity ids size //
    m_archiveFile.put( bitwiseIdSize );
    // Count entities //
    putIntToFile( m_folderNames.size() + m_fileNames.size(),
                  &m_archiveFile, sizeof( std::uintmax_t ) );


    // Catalog
    for( std::uintmax_t id : bitwiseCatalog ) {
        std::uintmax_t idSize;
        if( IS_FOLDER( id ) ) {
            id    |= id >> ( ( sizeof( std::uintmax_t ) - folderIdSize ) * 0x8 );
            idSize = folderIdSize;
        } else { // else file_flag //
            id    |= id >> ( ( sizeof( std::uintmax_t ) - fileIdSize ) * 0x8 );
            idSize = fileIdSize;
        }
        putIntToFile( id, &m_archiveFile, idSize );
    }
}

void Archive::m_packSingleFile( std::filesystem::path filePath ) {
    std::fstream file;
    file.open( filePath, std::ios::binary | std::ios::in );
    if( !file.is_open() ) {
        MSG_ERR( "Unable to open file " + filePath.string(), ERROR_OPEN_FILE );
        return;
    }

    std::uintmax_t fileSize = std::filesystem::file_size( filePath );
    m_archiveFile << std::setw( sizeof( std::uintmax_t ) );
    m_archiveFile.fill( 0x0 );
    putIntToFile( fileSize, &m_archiveFile, sizeof( std::uintmax_t ) );

    char * fileBuf = new char[ BUFFER_SIZE ];
    while( fileSize > BUFFER_SIZE ) {
        file.read( fileBuf, BUFFER_SIZE );
        m_archiveFile.write( fileBuf, BUFFER_SIZE );
        fileSize -= BUFFER_SIZE;
    }
    if( fileSize ) {
        file.read( fileBuf, fileSize );
        m_archiveFile.write( fileBuf, fileSize );
    }
    delete[] fileBuf;

    file.close();
    MSG_LOG( "File " + filePath.string() + " packed" );
}

void Archive::m_packFiles( void ) {
    for( auto entity : m_fileNames ) {
        if( std::filesystem::is_directory( entity ) ) continue;
        m_packSingleFile( entity );
    }
}


///////////////////////////////////////////////////////////////////////////////
//                           Extract Archive file                            //
///////////////////////////////////////////////////////////////////////////////

void Archive::m_extractSignature( void ) {
    char * archiveFlag = new char[ sizeof( ARCHIVE_FLAG ) ];
    m_archiveFile.read( archiveFlag, sizeof( ARCHIVE_FLAG ) - 1 );
    if( std::strcmp( archiveFlag, ARCHIVE_FLAG ) != 0 ) {
        m_archiveFile.close();
    }
}

void Archive::m_extractData( void ) {
    std::list< std::uintmax_t > bitwiseCatalog;
    std::list< std::uintmax_t > bitwiseNames;

    std::uint8_t               idSize;
    std::filesystem::file_type type;
    std::uintmax_t             letter;

    for( std::uint8_t i = 0; i < 2; i++ ) {
        if( i == 1 ) bitwiseNames.push_back( 0x0 );
        while( ( letter = m_archiveFile.get() ) != 0x0 ) {
            bitwiseNames.push_back( letter );
        }
    }
    m_normaliseNames( bitwiseNames );

    std::uint8_t bitwiseIdSize = m_archiveFile.get();
    std::uint8_t folderIdSize  = bitwiseIdSize >> 4;
    std::uint8_t fileIdSize    = bitwiseIdSize &  0xF;


    std::uintmax_t countEntities = getIntFromFile( &m_archiveFile, sizeof( std::uintmax_t ) );
    for( std::uintmax_t i = 0; i < countEntities; i++ ) {
        std::uintmax_t entityFlag, bitwiseEntity = m_archiveFile.get();

        std::uint8_t   idSize = ( IS_FOLDER8( bitwiseEntity ) ) ? folderIdSize : fileIdSize;

        entityFlag    = GET_FLAG8( bitwiseEntity ) << 0x38;
        bitwiseEntity = GET_ID8( bitwiseEntity );

        std::uintmax_t firstIdByte = bitwiseEntity << ( ( idSize - 1 ) * 0x8 );

        if( idSize - 1 ) {
            bitwiseEntity = getIntFromFile( &m_archiveFile, idSize - 1 );
        }

        bitwiseCatalog.push_back( entityFlag | firstIdByte | bitwiseEntity );
    }

    m_normaliseCatalog( bitwiseCatalog );
}

void Archive::m_extractSingleFile( std::filesystem::path filePath ) {
    std::fstream file;
    file.open( filePath, std::ios::binary | std::ios::out );
    if( !file.is_open() ) {
        MSG_ERR( "Unable to open file " + filePath.string(), ERROR_OPEN_FILE );
        return;
    }

    std::uintmax_t fileSize = getIntFromFile( &m_archiveFile, sizeof( std::uintmax_t ) );

    char * fileBuf = new char[ BUFFER_SIZE ];
    while( fileSize > BUFFER_SIZE ) {
        m_archiveFile.read( fileBuf, BUFFER_SIZE );
        file.write( fileBuf, BUFFER_SIZE );
        fileSize -= BUFFER_SIZE;
    }
    if( fileSize ) {
        m_archiveFile.read( fileBuf, fileSize );
        file.write( fileBuf, fileSize );
    }
    delete[] fileBuf;

    file.close();
    MSG_LOG( "File " + filePath.string() + " extracted" );
}

void Archive::m_extractFiles( void ) {
    for( auto fileName : m_fileNames ) {
        m_extractSingleFile( fileName );
    }
}
#undef BUFFER_SIZE


///////////////////////////////////////////////////////////////////////////////
//                                Manipulation                               //
///////////////////////////////////////////////////////////////////////////////

void Archive::pack( std::filesystem::path srcPath ) {
    m_srcPath = std::filesystem::absolute( srcPath ) / "";
    std::filesystem::path archivePath = m_srcPath.parent_path();
    archivePath.replace_extension( ARCHIVE_FLAG );
    archivePath = archivePath.filename();

    m_archiveFile.open( archivePath, std::ios::binary | std::ios::out );
    if( !m_archiveFile.is_open() ) {
        MSG_ERR( "Unable to open archive " + archivePath.string(), ERROR_OPEN_FILE );
        return;
    }

    m_packSignature();
    m_packData();
    if( g_error != ERROR_NON ) {
        m_archiveFile.close();
        std::filesystem::remove( srcPath );
        return;
    }
    MSG_LOG( "Metadata packed" );

    m_packFiles();
    if( g_error != ERROR_NON ) {
        m_archiveFile.close();
        std::filesystem::remove( srcPath );
        return;
    }
    MSG_LOG( "Entities packed" );

    m_archiveFile.close();
}

void Archive::extract( std::filesystem::path archivePath ) {
    if( !std::filesystem::is_regular_file( archivePath ) ) {
        MSG_ERR( "Unable to extract directory " + archivePath.string(), ERROR_DIRECTORY );
        return;
    }

    m_archiveFile.open( archivePath, std::ios::binary | std::ios::in );
    if( !m_archiveFile.is_open() ) {
        MSG_ERR( "Unable to open archive " + archivePath.string(), ERROR_OPEN_FILE );
        return;
    }

    m_extractSignature();
    if( !m_archiveFile.is_open() ) {
        MSG_ERR( "File " + archivePath.string() + " is not archive", ERROR_FILE );
        return;
    }

    m_srcPath = archivePath.filename().stem();
    std::filesystem::create_directory( m_srcPath );

    m_extractData();
    if( g_error != ERROR_NON ) {
        m_archiveFile.close();
        std::filesystem::remove_all( m_srcPath );
        return;
    }
    MSG_LOG( "Metadata extracted" );

    m_extractFiles();
    if( g_error != ERROR_NON ) {
        m_archiveFile.close();
        std::filesystem::remove_all( m_srcPath );
        return;
    }
    MSG_LOG( "Entities extracted" );

    m_archiveFile.close();
}
