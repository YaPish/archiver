#include "data.h"

DataBlock::DataBlock( uint8_t * bytes, std::size_t count, DataType dataType ) {
    std::memcpy( m_bytes, bytes, count );

    m_count    = count;
    m_dataType = dataType;
}

std::bitset< m_count * 8 > getBits() {

}

void DataBlock::setType( DataType dataType ) {
    m_dataType = dataType;
}

DataType DataBlock::getType() {
    return m_dataType;
}
