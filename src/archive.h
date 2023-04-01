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

    struct {
        Version            minVersion;
        CompressMethod     defaultCompressMethod;
        EncodeMethod       defaultEncodeMethod;
        std::uint8_t       bitwiseNameSize;
    } m_general;

    std::list< std::uint64_t > m_bitwiseCatalog;
    std::vector< std::string > m_folderNames;
    std::vector< std::string > m_fileNames;

    Catalog m_catalog;

private:
    void m_writeGeneral( std::ofstream & outputFile );
    void m_writeCatalog( std::ofstream & outputFile );
    void m_writeNames( std::ofstream & outputFile, std::filesystem::file_type type );
    void m_writeFiles( std::ofstream & outputFile );

    void m_readGeneral( std::ifstream & inputFile );
    void m_readCatalog( std::ifstream & inputFile );
    void m_readNames( std::ifstream & inputFile, std::filesystem::file_type type );
    void m_readFiles( std::ifstream & inputFile );

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


    void pack(
        std::string           archiveName,
        std::filesystem::path destGlobalPath
    );

    void extract(
        std::filesystem::path srcGlobalPath
    );
};

#endif
