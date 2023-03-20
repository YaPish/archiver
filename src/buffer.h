#ifndef _BUFFER_H_
#define _BUFFER_H_

class Buffer {
private:
    Archive  * archive;

    std::list< Byteset > dataBlocks;

public:
    Buffer()  = default;
    ~Buffer() = default;

    void newArchive();
    void convertArchiveToFile();

    /* blockSize == 0 -> EOF */
    void readFile( std::string filePath, std::size_t blockSize = 0 );
    void getData(  )
};

#endif
