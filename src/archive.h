#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

#include <cstdint>
#include <fstream>
#include <filesystem>
#include <list>

#include "def.h"


class Archive {
private:
    std::filesystem::path              m_srcPath;
    std::fstream                       m_archiveFile;

    std::uintmax_t                     m_folderId;
    std::uintmax_t                     m_fileId;

    std::list< std::filesystem::path > m_folderNames;
    std::list< std::filesystem::path > m_fileNames;

private:
    std::uintmax_t              m_idSize( std::filesystem::file_type type );

    void                        m_normaliseCatalog( std::list< std::uintmax_t > bitwiseView );
    void                        m_normaliseNames( std::list< std::uintmax_t > bitwiseView );

    std::list< std::uintmax_t > m_bitwiseContent( std::filesystem::path folderPath );
    std::list< std::uintmax_t > m_bitwiseCatalog( void );
    std::list< std::uintmax_t > m_bitwiseNames( void );

    void m_packSingleFile( std::filesystem::path filePath );
    void m_extractSingleFile( std::filesystem::path filePath );

    void m_packSignature( void );
    void m_packData( void );
    void m_packFiles( void );

    void m_extractSignature( void );
    void m_extractData( void );
    void m_extractFiles( void );

public:
    Archive( void ) = default;

    void pack( std::filesystem::path srcPath );
    void extract( std::filesystem::path archivePath );
};

#endif
