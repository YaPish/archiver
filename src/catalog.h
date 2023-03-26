#ifndef _CATALOG_H_
#define _CATALOG_H_

#include <cstdint>
#include <list>
#include <filesystem>


class Catalog {
private:
    std::filesystem::path m_localRoot;

public:
    Catalog();

    std::list< std::uint8_t > bitwiseView();

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
