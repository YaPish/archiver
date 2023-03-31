#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#include <cstdint>
#include <bitset>
#include <filesystem>

#include "def.h"
#include "catalog.h"


class Archive {
private:
    std::string m_path;

    std::bitset< ARCHIVE_SECTION_COUNT > m_sectionChange;

    struct {
        Version            minVersion;
        CompressMethod     defaultCompressMethod;
        EncodeMethod       defaultEncodeMethod;
        std::bitset< 8 >   wordSize;
    } m_general;

    Catalog m_catalog;

private:
    void m_writeGeneral( std::ofstream & outputFile );
    void m_writeNames( std::ofstream & outputFile, std::filesystem::file_type type );
    void m_writeCatalog( std::ofstream & outputFile );
    void m_writeFiles( std::ofstream & outputFile );

    void m_readGeneral( std::ofstream & inputFile );
    void m_readCatalog( std::ofstream & inputFile );
    void m_readFiles( std::ofstream & inputFile );

public:
    Archive( Version        minVersion            = VERSION_DEV_BETA,
             CompressMethod defaultCompressMethod = COMPRESS_METHOD_NON,
             EncodeMethod   defaultEncodeMethod   = ENCODE_METHOD_NON );

    Archive( std::filesystem::path srcGlobalPath );

    Version        minVersion() const;
    CompressMethod defaultCompressMethod() const;
    EncodeMethod   defaultEncodeMethod() const;

    std::uint8_t   countBytesFolderId() const;
    std::uint8_t   countBytesFileId() const;

    bool           hasChange();


    void add(
        std::filesystem::file_type pathType,
        std::filesystem::path srcGlobalPath,
        std::filesystem::path destLocalPath
    );
    void remove(
        std::filesystem::path srcLocalPath
    );
    void move(
        std::filesystem::path srcLocalPath,
        std::filesystem::path destLocalPath
    );


    void updatePack();
    void pack(
        std::string           archiveName,
        std::filesystem::path destGlobalPath
    );

    void extract(
        std::filesystem::path destGlobalPath
    );
};

#endif
