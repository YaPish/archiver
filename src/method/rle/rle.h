#ifndef _RLE_H_
#define _RLE_H_


#include <algorithm>
#include <iterator>
#include <fstream>
#include <filesystem>

#define BUFFER_SIZE   1024
#define MAX_ROW_BYTES 128


enum RleStatus {
    RLE_STATUS_NON           = 0x1,
    RLE_STATUS_SINGLE        = 0x80,
    RLE_STATUS_MULTIPLE      = 0x0
};


#endif
