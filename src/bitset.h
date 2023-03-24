#ifndef _BITSET_H_
#define _BITSET_H_

#include <cstdint>


class Bitset {
private:
    std::vector< std::uint8_t > m_data;
    std::size_t                 m_actualSize;
    bool                        m_defaultValue;

public:
    Bitset( std::size_t size = 0, bool defaultValue = 0 );

    // Element access //
    bool & operator[]( std::size_t index );

    bool all( bool value ) const;
    bool any( bool value ) const;
    bool none( bool value ) const;

    std::size_t count() const;

    // Modifiers //
    std::size_t size() const;
    void        size( std::size_t value );

    void        flip();
    void        flip( std::size_t index );

    void        reset();

    Bitset & operator&=( const Bitset & other );
    Bitset & operator|=( const Bitset & other );
    Bitset & operator^=( const Bitset & other );
    Bitset & operator~=();

    // Boolean operations //
    Bitset & operator&( const Bitset & other );
    Bitset & operator|( const Bitset & other );
    Bitset & operator^( const Bitset & other );
    Bitset & operator~();

    // Conversions //
    // Byteset toByteset() const;
};

#endif
