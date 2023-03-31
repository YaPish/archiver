#ifndef _DEF_H_
#define _DEF_H_

#define FILE_FLAG   0
#define FOLDER_FLAG 1
#define FOLDER_END  2


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
