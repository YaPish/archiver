#ifndef _FILE_H_
#define _FILE_H_

enum FileState {
    FILE_STATE_COMPRESS = 1,
    FILE_STATE_ENCODE   = 2
};

class File {
private:
    std::uint64_t  m_id;

    std::string    m_srcPath;

    CompressMethod m_compressMethod;
    EncodingMethod m_encodingMethod;

    Bitset         m_state;
    Byteset        m_data;

public:
    File(
        std::string    name,
        std::string    srcPath,
        CompressMethod compressMethod,
        EncodingMethod encodingMethod
    );

    struct state {
        bool isCompress() const;
        bool isEncode() const;
    };

    std::string name;

    void compress();
    void decompress();

    void encode();
    void decode();
};

#endif
