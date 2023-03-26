#include <iostream>
#include <filesystem>

#include "archive.h"

int main( int args, char ** argv ) {
    Archive test;
    test.add( std::filesystem::file_type::directory, argv[ 1 ], argv[ 2 ] );
    return 0;
}
