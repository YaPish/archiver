#ifndef _BYTESET_H_
#define _BYTESET_H_

class Byteset {
private:
    std::vector< std::uint8_t > data;

public:
    Byteset( std::size_t size );

    // Element access //
    std::uint8_t & operator[]( std::size_t index );

    // Modifiers //
    std::size_t size() const;
    void        size( std::size_t value );

    Byteset & operator&=( const Byteset & other );
    Byteset & operator|=( const Byteset & other );
    Byteset & operator^=( const Byteset & other );
    Byteset & operator~=( const Byteset & other );

    // Boolean operations //
    Byteset & operator&( const Byteset & other );
    Byteset & operator|( const Byteset & other );
    Byteset & operator^( const Byteset & other );
    Byteset & operator~( const Byteset & other );

    // Conversions //
    Bitset toBitset() const;
};

#endif
