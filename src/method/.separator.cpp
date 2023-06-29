#include "separator.h"

#define MIN_BLOCK_SIZE 8
#define MAX_BLOCK_SIZE 512

Separator::Separator( std::ifstream & stream )
    : m_stream( stream ) {
    m_blockSize = MAX_BLOCK_SIZE;
};

void Separator::setBlockSize( size_t value ) {
    if( value < MIN_BLOCK_SIZE && value > MAX_BLOCK_SIZE )
        return;
    m_blockSize = value;
}

size_t Separator::getBlockSize() const {
    return m_blockSize;
}

std::list< std::uint8_t > Separator::getBlock() {
    std::list< std::uint8_t > result = m_buffer;
    m_buffer.clear();

    size_t readDataSize = m_blockSize - result.size();
    char * readData = new char[ readDataSize ];
    m_stream.read( readData, readDataSize );
    for( size_t i = 0; i < readDataSize; i++ )
        result.push_back( static_cast< std::uint8_t >( readData[ i ] ) );

    return result;
}

void Separator::setUnusedBlock( std::list< std::uint8_t > block ) {
    m_buffer = block;
}
