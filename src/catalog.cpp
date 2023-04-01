#include <iostream>


#include <fstream>
#include <cmath>

#include "def.h"
#include "catalog.h"


Catalog::Catalog() {
    m_localRoot = std::filesystem::temp_directory_path() / "Archive_DEV";
    std::filesystem::create_directory( m_localRoot );
}

std::list< std::uint64_t > Catalog::m_getFolderContent( std::filesystem::path folder ) {
    std::list< std::uint64_t > result;
    std::uint64_t              folderPos = 0, filePos = 0;

    if ( !std::filesystem::is_directory( folder ) ||
          std::filesystem::is_empty( folder ) )
        return result;

    for( auto & entity : std::filesystem::directory_iterator( folder ) ) {
        auto entityPos = result.begin();

        switch( entity.status().type() ) {
            case std::filesystem::file_type::directory:
                std::advance( entityPos, folderPos++ );
                result.insert( entityPos, CODE_FOLDER( m_folderId++ ) );
                m_folderNames.push_back( entity.path().filename() );
                break;
            case std::filesystem::file_type::regular:
                std::advance( entityPos, folderPos + filePos++ );
                result.insert( entityPos, CODE_FILE( m_fileId++ ) );
                m_fileNames.push_back( entity.path().filename() );
                break;
        }
    }

    if( filePos || !( folderPos && filePos ) )
        result.back() = CODE_END( result.back() );
    return result;
}

std::list< std::uint64_t > Catalog::bitwiseCatalog() {
    m_folderNames.clear(); m_fileNames.clear();
    m_folderId = 1; m_fileId = 1;

    std::uint64_t              targetFolderId = 0;
    std::list< std::uint64_t > result;
    std::list< std::uint64_t > folderContent;

    auto folder = result.begin();
    folderContent = m_getFolderContent( m_localRoot );
    result.insert( folder, folderContent.begin(), folderContent.end() );

    for( auto & entity : std::filesystem::recursive_directory_iterator( m_localRoot ) ) {
        if( entity.status().type() != std::filesystem::file_type::directory ) continue;

        for( targetFolderId = 0; targetFolderId < m_folderNames.size(); targetFolderId++ ) {
            if( m_folderNames[ targetFolderId ] == entity.path().filename() ) break;
        }
        targetFolderId = CODE_FOLDER( targetFolderId );

        folder = std::find( result.begin(), result.end(), targetFolderId );
        folderContent = m_getFolderContent( entity.path() );

        if( folderContent.empty() ) {
            * folder = CODE_END( * folder );
        } else {
            std::advance( folder, 1 );
            result.insert( folder, folderContent.begin(), folderContent.end() );
        }
    }
    // ?
//    std::filesystem::remove_all( m_localRoot );

    return result;
}

std::list< std::uint64_t > Catalog::bitwiseNames( std::filesystem::file_type type ) {
    std::list< std::uint64_t > result;
    std::vector< std::string > srcNames;
    std::uint64_t              srcNameSize = nameSize( type );

    switch( type ) {
        case std::filesystem::file_type::directory:
            srcNames = m_folderNames;
            break;
        case std::filesystem::file_type::regular:
            srcNames = m_fileNames;
            break;
    }

    for( std::uint64_t i = 0; i < srcNames.size(); i++ ) {
        // delta to next //
        result.push_back( srcNames[ i ].size() );

        // ascii name //
        for( char c : srcNames[ i ] )
            result.push_back( static_cast< std::uint64_t >( c ) );
    }
    return result;
}

std::uint64_t Catalog::nameSize( std::filesystem::file_type type ) {
    std::uint64_t result = 0;
    std::uint64_t srcNameSize;
    switch( type ) {
        case std::filesystem::file_type::directory:
            srcNameSize = m_folderId;
            break;
        case std::filesystem::file_type::regular:
            srcNameSize = m_fileId;
            break;
    }
    while( srcNameSize ) {
        srcNameSize = srcNameSize >> ( result ? 8 : 6 );
        result++;
    }
    return result;
}


void Catalog::add( std::filesystem::file_type pathType,
                   std::filesystem::path srcGlobalPath,
                   std::filesystem::path destLocalPath ) {
    std::filesystem::path wholePath = m_localRoot / destLocalPath / srcGlobalPath;
    std::filesystem::path directoryPath = m_localRoot / destLocalPath;

    if( !std::filesystem::is_directory( directoryPath )
     ||  std::filesystem::exists( wholePath ) )
        return;

    switch( pathType ) {
        case std::filesystem::file_type::directory:
            std::filesystem::create_directory( wholePath );
            break;
        case std::filesystem::file_type::regular:
            std::ofstream newFile( wholePath );
            break;
    }
}

void Catalog::remove( std::filesystem::path srcLocalPath ) {
    if( !std::filesystem::exists( m_localRoot / srcLocalPath ) )
        return;
    std::filesystem::remove_all( m_localRoot / srcLocalPath );
}

void Catalog::move( std::filesystem::path srcLocalPath,
                    std::filesystem::path destLocalPath ) {

}
