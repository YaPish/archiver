#ifndef _DEF_H_
#define _DEF_H_

#define FILE_FLAG   0x0  // 0000 0000 //
#define FOLDER_FLAG 0x80 // 1000 0000 //
#define FOLDER_END  0x40 // 0100 0000 //

#define CODE_FOLDER( id ) ( id | ( static_cast< std::uint64_t >( FOLDER_FLAG ) << 0x38 ) ) // for uint64 id
#define CODE_FILE( id )   ( id | ( static_cast< std::uint64_t >( FILE_FLAG )   << 0x38 ) ) // for uint64 id
#define CODE_END( id )    ( id | ( static_cast< std::uint64_t >( FOLDER_END )  << 0x38 ) ) // for uint64 id

#define GET_ID( code )    ( code & 0x3fffffffffffffff )     // for uint64 code

//////////////////
//    Version   //
// Size: 1 byte //
//////////////////
enum Version {
    VERSION_DEV_BETA = 0
};

////////////////////
// CompressMethod //
//  Size: 1 byte  //
////////////////////
enum CompressMethod {
    COMPRESS_METHOD_NON = 0,
    COMPRESS_METHOD_RLE = 1
};

////////////////////
// EncodingMethod //
//  Size: 1 byte  //
////////////////////
enum EncodeMethod {
    ENCODE_METHOD_NON = 0
};


#define ARCHIVE_SECTION_COUNT 3
enum ArchiveSection {
    ARCHIVE_SECTION_GENERAL = 1,
    ARCHIVE_SECTION_CATALOG = 2,
    ARCHIVE_SECTION_FILES   = 4
};

#endif
