#ifndef _BUFFER_H_
#define _BUFFER_H_

class Buffer {
private:
    Archive  * archive;

    uint8_t * data;
    size_t    dataSize;

public:
    Buffer()  = default;
    ~Buffer() = default;

    void newArchive();
    void convertArchiveToFile();

    void readFile( std::string filePath, size_t blockSize = 0 );
    void getData(  )
};

#endif
