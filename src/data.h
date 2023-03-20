#ifndef _DATA_H_
#define _DATA_H_

enum DataType {
    DATA_TYPE_BIN,
    DATA_TYPE_BYTE
};

class DataBlock {
private:
    DataType    m_dataType;

    uint8_t *   m_bytes;
    std::size_t m_count;

public:
    DataBlock(
        uint8_t * bytes,
        size_t    count,
        DataType  dataType = DATA_TYPE_BYTE
    );
    ~DataBlock() = default;

    void     setType( DataType dataType );
    DataType getType();
};

#endif
