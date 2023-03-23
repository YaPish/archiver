#ifndef _DEF_H_
#define _DEF_H_


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
    COMPRESS_METHOD_NON = 0
    COMPRESS_METHOD_RLE = 1
};

////////////////////
// EncodingMethod //
//  Size: 1 byte  //
////////////////////
enum EncodingMethod {
    ENCODING_METHOD_NON = 0
};


#endif
