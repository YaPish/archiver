#ifndef _DEF_H_
#define _DEF_H_

#include <cstdint>
#include <iostream>

struct Command {
    std::string name;
    int         countArgs;
};

inline const Command COMMANDS[] = {
    { std::string( "pack" ),       1 },
    { std::string( "extract" ),    1 },
    { std::string( "compress" ),   2 },
    { std::string( "decompress" ), 1 }
};

inline int g_error;

#define ERROR_NON             0

#define ERROR_COMMAND         11
#define ERROR_COUNT           12
#define ERROR_OPEN_FILE       13

#define ERROR_DIRECTORY       20
#define ERROR_FILE            21

#define ERROR_COMPRESS        30
#define ERROR_DECOMPRESS      31

#define ERROR_PACK            40
#define ERROR_PACK_NAME       41
#define ERROR_PACK_CATALOG    42
#define ERROR_PACK_FILE       43

#define ERROR_EXTRACT         50
#define ERROR_EXTRACT_NAME    51
#define ERROR_EXTRACT_CATALOG 52
#define ERROR_EXTRACT_FILE    53

// TODO: log file
#define MSG_LOG( __MSG__ ) std::cout << __MSG__ << std::endl
#define MSG_WRN( __MSG__ ) std::cout << "WARNING: " << __MSG__ << std::endl
#define MSG_ERR( __MSG__, __ERR_ID__ ) std::cerr << "ERROR: " << __MSG__ << std::endl; g_error = __ERR_ID__


#define ARCHIVE_FLAG      "yap"
#define DIRECTORY_PLUGINS "/usr/local/share/yap/"

#define FILE_FLAG    0x0  // 0000 0000 //
#define FOLDER_FLAG  0x80 // 1000 0000 //
#define FOLDER_END   0x40 // 0100 0000 //


///////////////////////////////////////////////////////////////////////////////
//                                 64 Bits                                   //
///////////////////////////////////////////////////////////////////////////////

#define CODE_FOLDER( __ID__ )  ( __ID__   | ( static_cast< std::uintmax_t >( FOLDER_FLAG ) << 0x38 ) )
#define CODE_FILE( __ID__ )    ( __ID__   | ( static_cast< std::uintmax_t >( FILE_FLAG )   << 0x38 ) )
#define CODE_END( __ID__ )     ( __ID__   | ( static_cast< std::uintmax_t >( FOLDER_END )  << 0x38 ) )

#define IS_FOLDER( __CODE__ )  ( __CODE__ & ( static_cast< std::uintmax_t >( FOLDER_FLAG ) << 0x38 ) )
#define IS_END( __CODE__ )     ( __CODE__ & ( static_cast< std::uintmax_t >( FOLDER_END )  << 0x38 ) )

#define GET_ID( __CODE__ )     ( __CODE__ & 0x3fffffffffffffff )
#define GET_FLAG( __CODE__ )   ( __CODE__ & ( static_cast< std::uintmax_t >( FOLDER_FLAG | FOLDER_END ) << 0x38 ) )


///////////////////////////////////////////////////////////////////////////////
//                                  8 Bits                                   //
///////////////////////////////////////////////////////////////////////////////

#define IS_FOLDER8( __CODE__ ) ( __CODE__ & FOLDER_FLAG )
#define IS_END8( __CODE__ )    ( __CODE__ & FOLDER_END )

#define GET_ID8( __CODE__ )    ( __CODE__ & 0x3f )
#define GET_FLAG8( __CODE__ )  ( __CODE__ & ( FOLDER_FLAG | FOLDER_END ) )


#endif
