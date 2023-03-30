#include <iostream>


#include <fstream>

#include "catalog.h"


#define FILE_FLAG   0
#define FOLDER_FLAG 1

#define FOLDER_END  2


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
                result.insert( entityPos, ( m_folderId++ << 2 ) | FOLDER_FLAG );
                m_folderNames.push_back( entity.path().filename() );
                break;
            case std::filesystem::file_type::regular:
                std::advance( entityPos, folderPos + filePos++ );
                result.insert( entityPos, ( m_fileId++ << 2 ) | FILE_FLAG );
                m_fileNames.push_back( entity.path().filename() );
                break;
        }
    }

    if( filePos || !( folderPos && filePos ) )
        result.back() |= FOLDER_END;
    return result;
}

std::list< std::uint64_t > Catalog::bitwiseView() {
    m_folderNames.clear(); m_fileNames.clear();
    m_folderId = 0; m_fileId = 0;

    std::uint64_t              targetFolderId = 0;
    std::list< std::uint64_t > result;
    std::list< std::uint64_t > folderContent;

    auto folder = result.begin();
    folderContent = m_getFolderContent( m_localRoot );
    result.insert( folder, folderContent.begin(), folderContent.end() );

    for( auto & entity : std::filesystem::recursive_directory_iterator( m_localRoot ) ) {
        if( entity.status().type() != std::filesystem::file_type::directory )
            continue;

        for( targetFolderId = 0; targetFolderId < m_folderNames.size(); targetFolderId++ ) {
            if( m_folderNames[ targetFolderId ] == entity.path().filename() ) break;
        }
        targetFolderId = ( ( targetFolderId << 2 ) | FOLDER_FLAG );

        folderContent = m_getFolderContent( entity.path() );
        if( folderContent.empty() ) {
            * folder |= FOLDER_END;
        } else {
            std::advance( folder, 1 );
            result.insert( folder, folderContent.begin(), folderContent.end() );
        }
    }
    std::filesystem::remove_all( m_localRoot );

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
