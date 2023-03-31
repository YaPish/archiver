#include <iostream>
#include <fstream>
#include <filesystem>

#include "archive.h"

int main( int args, char ** argv ) {
    Archive test;
//    test.add( std::filesystem::file_type::regular, "file0", "." );
//    test.add( std::filesystem::file_type::regular, "file1", "." );
    test.add( std::filesystem::file_type::directory, "folder0", "." );
    test.add( std::filesystem::file_type::directory, "folder1", "." );

//    test.add( std::filesystem::file_type::regular, "file2", "./folder0" );
//    test.add( std::filesystem::file_type::regular, "file3", "./folder0" );

//    test.add( std::filesystem::file_type::regular, "file4", "./folder1" );

    test.add( std::filesystem::file_type::directory, "folder2", "./folder1" );
//    test.add( std::filesystem::file_type::regular, "file5", "./folder1/folder2" );
//    test.add( std::filesystem::file_type::regular, "file6", "./folder1/folder2" );
//    test.add( std::filesystem::file_type::regular, "file7", "./folder1/folder2" );
//    test.add( std::filesystem::file_type::regular, "file4", "./folder2" );
//    test.add( std::filesystem::file_type::regular, "file5", "./folder1/folder3" );
 //   test.add( std::filesystem::file_type::regular, "file6", "./folder1/folder3" );
    test.pack( "TestArchive.yap", "." );
    return 0;
}
