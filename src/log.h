#ifndef _LOG_H_
#define _LOG_H_

#include <ostream>
#include <chrono>
#include <string>


#define LOG_INIT()                                 \
    static std::ofstream __LOG_FILE__;             \
    __LOG_FILE__.open( "log.txt", std::ios::out ); \
    static auto __START_TIME__                     \
        = std::chrono::steady_clock::now();


#define LOG_MSG( __MSG__ )                                                         \
    std::chrono::duration< double > __SECONDS__                                    \
        = std::chrono::steady_clock::now() - __START_TIME__;                       \
    __LOG_FILE__ << ": " << __MSG__ << std::endl

#define LOG_WRN( __MSG__ )                                                         \
    __LOG_FILE__ << ( __SECONDS__ ).count();                                       \
    __LOF_FILE__ << " WARNING: " << __MSG__ << std::endl

#define LOG_ERR( __MSG__, __ERR_ID__ )                                             \
    __LOG_FILE__ << ( __SECONDS__ ).count();                                       \
    __LOF_FILE__ << " ERROR: " << __MSG__ << std::endl; exit( __ERR_ID__ )


#endif
