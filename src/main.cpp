#include <iostream>
#include <ios>

/*
#include "buffer.h"
#include "controller.h"
#include "executor.h"
*/

int main( int args, char ** argv ) {
    int i = 241;
    std::cout << std::hex << i << " | "
        << std::bitset< 8 >( i ) << std::endl;
    return 0;
}
