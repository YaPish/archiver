#include <iostream>
#include <fstream>
#include <filesystem>

#include "archive.h"

Archive::Archive(
    Version        minVersion,
    CompressMethod defaultCompressMethod,
    EncodeMethod   defaultEncodeMethod ) {
    m_general.minVersion            = minVersion;
    m_general.defaultCompressMethod = defaultCompressMethod;
    m_general.defaultEncodeMethod   = defaultEncodeMethod;
}

Archive::Archive( std::filesystem::path srcGlobalPath ) {

}


///////////////////////////
// Write to Archive file //
///////////////////////////

void Archive::m_writeGeneral( std::ofstream & outputFile ) {
    if( m_general.minVersion >= VERSION_DEV_BETA ) {
        outputFile.put( m_general.minVersion );
        outputFile.put( m_general.defaultCompressMethod );
        outputFile.put( m_general.defaultEncodeMethod );
        // TODO
    }
}

void Archive::m_writeNames( std::ofstream & outputFile, std::filesystem::file_type type ) {
    std::list< std::uint64_t > bitwiseNames = m_catalog.bitwiseNames( type );
    std::uint64_t              nameSize = m_catalog.nameSize( type );

    auto entity = bitwiseNames.begin();
    while( entity != bitwiseNames.end() ) {
        for( std::uint64_t i = 0; i < * entity || entity != bitwiseNames.end(); i++ ) {
            outputFile.put( * entity );
            std::advance( entity, 1 );
        }
    }
    outputFile.put( 0x0 );
}

void Archive::m_writeCatalog( std::ofstream & outputFile ) {
    m_bitwiseCatalog = m_catalog.bitwiseCatalog();

    std::uint64_t folderNameSize = m_catalog.nameSize( std::filesystem::file_type::directory );
    std::uint64_t fileNameSize   = m_catalog.nameSize( std::filesystem::file_type::regular );

    std::uint8_t bitwiseNameSize = ( static_cast< std::uint8_t >( folderNameSize ) << 4 )
                                 | ( static_cast< std::uint8_t >( fileNameSize ) & 0xF );
    outputFile.put( bitwiseNameSize ); // add to general about names size //

    std::uint64_t nameSize;
    for( std::uint64_t i : m_bitwiseCatalog ) {
        if( i & FOLDER_FLAG ) {
            i |= i >> ( ( 8 - folderNameSize ) * 8 );
            nameSize = folderNameSize;
        } else { // else file_flag //
            i |= i >> ( ( 8 - fileNameSize ) * 8 );
            nameSize = fileNameSize;
        }
        outputFile.write( reinterpret_cast< char * >( & i ), nameSize );
    }
    outputFile.put( 0x0 );
}

void Archive::m_writeFiles( std::ofstream & outputFile ) {
    // TODO
}


////////////////////////////
// Read from Archive file //
////////////////////////////

void Archive::m_readGeneral( std::ifstream & inputFile ) {
    m_general.minVersion = static_cast< Version >( inputFile.get() );

    if( m_general.minVersion >= VERSION_DEV_BETA ) {
        m_general.defaultCompressMethod = static_cast< CompressMethod >( inputFile.get() );
        m_general.defaultEncodeMethod   = static_cast< EncodeMethod >( inputFile.get() );
    }

    // last general byte //
    m_general.bitwiseNameSize = static_cast< std::uint8_t >( inputFile.get() );
}

void Archive::m_readNames( std::ifstream & inputFile, std::filesystem::file_type type ) {
    std::string  name;
    std::uint8_t nameSize = inputFile.get();
    for( ; nameSize != 0; nameSize = inputFile.get() ) {
        inputFile.read( reinterpret_cast< char * >( & name ), nameSize );
        m_folderNames.push_back( name );
    }
}

void Archive::m_readCatalog( std::ifstream & inputFile ) {
    // check if no move ? //
    std::uint8_t folderNameSize = m_general.bitwiseNameSize >> 4;
    std::uint8_t fileNameSize   = m_general.bitwiseNameSize & 0xF;

    std::uint8_t               nameSize;
    std::filesystem::file_type type;

    std::uint64_t bitwiseEntity = inputFile.get();
    for( ; bitwiseEntity != 0; bitwiseEntity = inputFile.get() ) {
        std::uint64_t tmp = bitwiseEntity << 0x38;

        nameSize = ( bitwiseEntity | FOLDER_FLAG ? folderNameSize : fileNameSize );
        type     = ( bitwiseEntity | FOLDER_FLAG ? std::filesystem::file_type::directory
                                                 : std::filesystem::file_type::regular );

        inputFile.read( reinterpret_cast< char * >( & bitwiseEntity ), nameSize - 1 );
        bitwiseEntity |= tmp;

        m_bitwiseCatalog.push_back( bitwiseEntity );
    }
}

void Archive::m_readFiles( std::ifstream & inputFile ) {
    // TODO
}


/////////////////////////////
// Get General Information //
/////////////////////////////

Version Archive::minVersion() const {
    return m_general.minVersion;
}

CompressMethod Archive::defaultCompressMethod() const {
    return m_general.defaultCompressMethod;
}

EncodeMethod Archive::defaultEncodeMethod() const {
    return m_general.defaultEncodeMethod;
}

std::uint8_t Archive::countBytesFolderId() const {

}

std::uint8_t Archive::countBytesFileId() const {

}


//////////////////
// Manipulation //
//////////////////

void Archive::add( std::filesystem::file_type pathType,
                   std::filesystem::path srcGlobalPath,
                   std::filesystem::path destLocalPath ) {
    // TODO
    m_catalog.add( pathType, srcGlobalPath, destLocalPath );
}

void Archive::remove( std::filesystem::path srcLocalPath ) {
    m_catalog.remove( srcLocalPath );
}

void Archive::move( std::filesystem::path srcLocalPath,
                    std::filesystem::path destLocalPath ) {

}

void Archive::pack( std::string           archiveName,
                    std::filesystem::path destGlobalPath ) {
    if( !std::filesystem::is_directory( destGlobalPath ) )
        return;

    std::ofstream outputFile( destGlobalPath / archiveName,
                              std::ios::binary | std::ios::out );
    if ( !outputFile.is_open() )
        return;

    m_writeGeneral( outputFile );
    m_writeCatalog( outputFile );
    m_writeNames( outputFile, std::filesystem::file_type::directory );
    m_writeNames( outputFile, std::filesystem::file_type::regular );
    m_writeFiles( outputFile );

    outputFile.close();
}

void Archive::extract( std::filesystem::path srcGlobalPath ) {
    if( !std::filesystem::is_regular_file( srcGlobalPath ) ||
        !std::filesystem::exists( srcGlobalPath ) )
        return;

    std::ifstream inputFile( srcGlobalPath, std::ios::binary | std::ios::in );
    if( !inputFile.is_open() )
        return;

    m_readGeneral( inputFile );
    m_readCatalog( inputFile );
    m_readNames( inputFile, std::filesystem::file_type::directory );
    m_readNames( inputFile, std::filesystem::file_type::regular );
    m_readFiles( inputFile );

    inputFile.close();
}
