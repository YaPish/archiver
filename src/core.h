#ifndef _CORE_H_
#define _CORE_H_

#include <fstream>
#include <filesystem>

#include "archive.h"


class Core {
private:
    std::filesystem::path m_pipeFifoPath;
    std::fstream          m_pipeFifo;

    Archive               m_archive;

public:
    Core( void ) = default;

    void pack( std::filesystem::path srcPath );
    void extract( std::filesystem::path archivePath );

    void compress( std::filesystem::path srcPath, std::string method );
    void decompress( std::filesystem::path srcPath );
};

#endif
