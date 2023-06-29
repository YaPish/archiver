#ifndef _CORE_H_
#define _CORE_H_

#include <fstream>
#include <filesystem>

#include "archive.h"


#define COMMAND_PACK        1  // ( 1 args ) srcGlobalPath
#define COMMAND_EXTRACT     2  // ( 1 args ) srcGlobalPath
#define COMMAND_COMPRESS    3  // ( 2 args ) srcLocalPath
#define COMMAND_DECOMPRESS  4  // ( 1 args ) srcLocalPath


enum CoreStatus {
    CORE_STATUS_NON       = 0,
    CORE_STATUS_AVAILABLE = 1
};


class Core {
private:
    CoreStatus            m_status;

    std::filesystem::path m_pipeFifoPath;
    std::fstream          m_pipeFifo;

    Archive               m_archive;

private:
    void m_executeFifo();
    void m_clearFifo();

public:
    Core( void );

    void init( void );
    void update( void );

    void __exetest( int args, char ** argv );

    void pack( std::filesystem::path srcPath );
    void extract( std::filesystem::path archivePath );

    void compress( std::filesystem::path srcPath, std::string method );
    void decompress( std::filesystem::path srcPath );
};

#endif
