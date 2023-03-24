#ifndef _BUFFER_H_
#define _BUFFER_H_

class Buffer {
private:
    Archive * m_archive;

public:
    struct archive {
        void clear();
        void getOutputFile();
    };

    struct file {
        void add(
            std::string path,
            std::string name,
            std::size_t blockSize = 0
        );
        void remove( std::string name );
    };

    void newArchive();
    void convertArchiveToFile();

    /* blockSize == 0 -> EOF */
    void readFile( std::string filePath, std::size_t blockSize = 0 );
    void getData(  )
};

#endif
