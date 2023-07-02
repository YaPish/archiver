#ifndef _DEF_H_
#define _DEF_H_

#include <iostream>


inline int g_error;

#define ERROR_NON 0

#define ERROR_DIRECTORY 1
#define ERROR_FILE 13

#define ERROR_OPEN_FILE 2

#define ERROR_COMPRESS 3
#define ERROR_DECOMPRESS 12

#define ERROR_PACK 4
#define ERROR_PACK_NAME 6
#define ERROR_PACK_CATALOG 7
#define ERROR_PACK_FILE 8

#define ERROR_EXTRACT 5
#define ERROR_EXTRACT_NAME 9
#define ERROR_EXTRACT_CATALOG 10
#define ERROR_EXTRACT_FILE 11

// TODO: log file
#define MSG_LOG( __MSG__ ) std::cout << __MSG__ << std::endl
#define MSG_WRN( __MSG__ ) std::cout << "WARNING: " << __MSG__ << std::endl
#define MSG_ERR( __MSG__, __ERR_ID__ ) std::cerr << "ERROR: " << __MSG__ << std::endl; g_error = __ERR_ID__


#define ARCHIVE_FLAG "yap"

#define FILE_FLAG    0x0  // 0000 0000 //
#define FOLDER_FLAG  0x80 // 1000 0000 //
#define FOLDER_END   0x40 // 0100 0000 //


///////////////////////////////////////////////////////////////////////////////
//                                 64 Bits                                   //
///////////////////////////////////////////////////////////////////////////////

#define CODE_FOLDER( __ID__ )  ( __ID__ | ( static_cast< std::uintmax_t >( FOLDER_FLAG ) << 0x38 ) )
#define CODE_FILE( __ID__ )    ( __ID__ | ( static_cast< std::uintmax_t >( FILE_FLAG )   << 0x38 ) )
#define CODE_END( __ID__ )     ( __ID__ | ( static_cast< std::uintmax_t >( FOLDER_END )  << 0x38 ) )

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
