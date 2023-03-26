#include <iostream>


#include <fstream>

#include "catalog.h"


Catalog::Catalog() {
    m_localRoot = std::filesystem::temp_directory_path() / "Archive_DEV";
    std::filesystem::create_directory( m_localRoot );
}

std::list< std::uint8_t > Catalog::bitwiseView() {

}

void Catalog::add( std::filesystem::file_type pathType,
                   std::filesystem::path srcGlobalPath,
                   std::filesystem::path destLocalPath ) {
    if( !std::filesystem::is_directory( m_localRoot / destLocalPath ) )
        return;


    std::cout << m_localRoot / destLocalPath << std::endl;


    if( pathType == std::filesystem::file_type::directory ) {
        if( !std::filesystem::exists( srcGlobalPath ) )
            return;

        std::filesystem::create_directory( m_localRoot / srcGlobalPath );
    } else if( pathType == std::filesystem::file_type::regular ) {
        if( !std::filesystem::exists(
                    std::filesystem::absolute( srcGlobalPath ) )
         ||  std::filesystem::exists( m_localRoot / destLocalPath /
                    std::filesystem::absolute( srcGlobalPath ) ) )
            return;

        std::fstream newFile( m_localRoot / destLocalPath /
                              std::filesystem::absolute( srcGlobalPath ) );
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
