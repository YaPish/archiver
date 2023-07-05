#include <iostream>
#include <filesystem>
#include <string>
#include <sys/stat.h>

int main( int argc, char ** argv ) {
    /* argv[ 1 ] - method   |   argv[ 2  ] - path */
    if( argc != 3 ) return -1;
    std::string commandCompress = "yap compress ", commandDecompress = "yap decompress ";
    std::string commandArgs     = std::string( argv[ 1 ] ) + std::string( argv[ 2 ] );

    std::uintmax_t srcFileSize = std::filesystem::file_size( std::filesystem::path( argv[ 2 ] ) );

    auto startTime = std::chrono::system_clock::now();
    if( !std::system( ( commandCompress + commandArgs ).c_str() ) ) return -2;
    auto endTime   = std::chrono::system_clock::now();
    std::chrono::duration< double > compressTime = endTime - startTime;

    std::uintmax_t destFileSize = std::filesystem::file_size( std::filesystem::path( argv[ 2 ] ) );

    startTime = std::chrono::system_clock::now();
    if( !std::system( ( commandDecompress + commandArgs ).c_str() ) ) return -2;
    endTime   = std::chrono::system_clock::now();
    std::chrono::duration< double > decompressTime = endTime - startTime;

    std::cout << "Src            size: " << srcFileSize  << std::endl;
    std::cout << "Dest           size: " << destFileSize << std::endl;
    std::cout << "Compress       time: " << compressTime.count()   << std::endl;
    std::cout << "Decompress     time: " << decompressTime.count() << std::endl;
    std::cout << "Compress      ratio: " << ( srcFileSize / destFileSize ) << std::endl;
    std::cout << "Compress   velocity: " << ( srcFileSize / compressTime.count() ) << std::endl;
    std::cout << "Decompress velocity: " << ( destFileSize / decompressTime.count() ) << std::endl << std::endl;
    std::cout << "Symmetry: " << ( compressTime.count() / decompressTime.count() ) << std::endl;

    return 0;
}
