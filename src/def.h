#ifndef _DEF_H_
#define _DEF_H_

#define ARCHIVE_FLAG "yap"

#define FILE_FLAG   0x0  // 0000 0000 //
#define FOLDER_FLAG 0x80 // 1000 0000 //
#define FOLDER_END  0x40 // 0100 0000 //


///////////////////////////////////////////////////////////////////////////////
//                                 64 Bits                                   //
///////////////////////////////////////////////////////////////////////////////

#define CODE_FOLDER( __ID__ )  ( __ID__ | ( static_cast< std::uint64_t >( FOLDER_FLAG ) << 0x38 ) )
#define CODE_FILE( __ID__ )    ( __ID__ | ( static_cast< std::uint64_t >( FILE_FLAG )   << 0x38 ) )
#define CODE_END( __ID__ )     ( __ID__ | ( static_cast< std::uint64_t >( FOLDER_END )  << 0x38 ) )

#define IS_FOLDER( __CODE__ )  ( __CODE__ & ( static_cast< std::uint64_t >( FOLDER_FLAG ) << 0x38 ) )
#define IS_END( __CODE__ )     ( __CODE__ & ( static_cast< std::uint64_t >( FOLDER_END )  << 0x38 ) )

#define GET_ID( __CODE__ )     ( __CODE__ & 0x3fffffffffffffff )
#define GET_FLAG( __CODE__ )   ( __CODE__ & ( static_cast< std::uint64_t >( FOLDER_FLAG | FOLDER_END ) << 0x38 ) )


///////////////////////////////////////////////////////////////////////////////
//                                  8 Bits                                   //
///////////////////////////////////////////////////////////////////////////////

#define IS_FOLDER8( __CODE__ ) ( __CODE__ & FOLDER_FLAG )
#define IS_END8( __CODE__ )    ( __CODE__ & FOLDER_END )

#define GET_ID8( __CODE__ )    ( __CODE__ & 0x3f )
#define GET_FLAG8( __CODE__ )  ( __CODE__ & ( FOLDER_FLAG | FOLDER_END ) )


#endif
