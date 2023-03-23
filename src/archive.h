#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_


class Archive {
private:
    struct m_generalInformation {
        const std::uint8_t length; // Count bytes to next section //

        Version            minVersion;
        CompressMethod     defaultCompressMethod;
        EncodeMethod       defaultEncodeMethod;
        Bitset             wordSize;
    };

    Catalog m_catalog;

public:
    Archive( Version          minVersion            = VERSION_DEV_BETA,
             CompressedMethod defaultCompressMethod = COMPRESS_METHOD_RLE,
             std::uint8_t     fileCountBytes        = 1,
             std::uint8_t     folderCountBytes      = 1 );
    Version        getMinVersion();
    CompressMethod getDefaultCompressMethod();
    EncodeMethod   getDefaultEncodeMethod();

    void createOutputFile();
};

#endif
