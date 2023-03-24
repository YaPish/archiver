#include <cmath>
#include <climits>

#include "bitset.h"


Bitset::Bitset( std::size_t size, bool defaultValue )
    : m_actualSize( size ) {
    for( std::size_t i = 0; i < std::round( size / ( double )CHAR_BIT ); i++ )
        m_data.push_back( defaultValue ? UCHAR_MAX : 0 );
};

bool & Bitset::operator[]( std::size_t index ) {
    try {
        bool result = false;
        if ( index < m_actualSize )
            return m_data[ index / ( double )CHAR_BIT ];
        else
            throw result;
    } catch ( ... ) {}
}

bool Bitset::all( bool value ) const {
    for( std::size_t i = 0; i < m_data.size(); i++ ) {
        if( value ? ( m_data[ i ] != UCHAR_MAX ) : ( m_data[ i ] != 0 ) )
            return false;
    }
    return true;
}

bool Bitset::any( bool value ) const {
    for( std::size_t i = 0; i < m_data.size(); i++ ) {
        if( value ? ( m_data[ i ] != 0 ) : ( m_data[ i ] != UCHAR_MAX ) )
            return true;
    }
    return false;
}

bool Bitset::none( bool value ) const {
    for( std::size_t i = 0; i < m_data.size(); i++ ) {
        if( value ? ( m_data[ i ] != 0 ) : ( m_data[ i ] != UCHAR_MAX ) )
            return false;
    }
    return true;
}

std::size_t Bitset::count() const {
}

std::size_t Bitset::size() const {
    return m_actualSize;
}

void Bitset::size( std::size_t value ) {
    if( value / ( double )CHAR_BIT == m_actualSize / ( double )CHAR_BIT )
        m_actualSize = value;
    else {
        // TODO
    }
}

void Bitset::flip() {
    for( std::size_t i = 0; i < m_data.size(); i++ )
        m_data[ i ] ~= m_data[ i ];
}

void Bitset::flip( std::size_t index ) {
    // TODO
}

void Bitset::reset() {
    for( std::size_t i = 0; i < m_data.size(); i++ )
        m_data[ i ] = ( m_defaultValue ? UCHAR_MAX : 0 );
}
