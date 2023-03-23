#ifndef _FILE_H_
#define _FILE_H_

class File {
private:
    std::uint64_t  m_id;

    std::string    m_srcPath;

    CompressMethod m_compressMethod;
    EncodingMethod m_encodingMethod;

    bool           m_isCompressed;
    bool           m_isEncoded;
    Byteset        m_data;

public:
    File(
        std::string    name,
        std::string    srcPath,
        CompressMethod compressMethod,
        EncodingMethod encodingMethod
    );

    std::string name;

    void compress();
    void decompress();

    void encode();
    void decode();
};

#endif
