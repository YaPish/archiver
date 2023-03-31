#ifndef _CATALOG_H_
#define _CATALOG_H_

#include <cstdint>
#include <list>
#include <vector>
#include <string>
#include <filesystem>


class Catalog {
private:
    std::filesystem::path      m_localRoot;

    std::vector< std::string > m_folderNames;
    std::vector< std::string > m_fileNames;

    std::uint64_t              m_folderId;
    std::uint64_t              m_fileId;
private:
    std::list< std::uint64_t > m_getFolderContent(
        std::filesystem::path folder
    );

public:
    Catalog();

    std::uint64_t              nameSize(
        std::filesystem::file_type type
    );

    std::list< std::uint64_t > bitwiseCatalog();
    std::list< std::uint64_t > bitwiseNames(
        std::filesystem::file_type type
    );

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
};


#endif
