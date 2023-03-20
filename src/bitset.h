#ifndef _BITSET_H_
#define _BITSET_H_

class Bitset {
private:
    std::vector< std::uint8_t > data;
    std::size_t                 actualSize;

public:
    Bitset( std::size_t size );

    // Element access //
    bool & operator[]( std::size_t index );

    bool all( bool value ) const;
    bool any( bool value ) const;
    bool none( bool value ) const;

    std::size_t count() const;

    // Modifiers //
    std::size_t size() const;
    void        size( std::size_t value );

    Bitset &    flip();
    Bitset &    flip( std::size_t index );

    Bitset &    reset();

    Bitset & operator&=( const Bitset & other );
    Bitset & operator|=( const Bitset & other );
    Bitset & operator^=( const Bitset & other );
    Bitset & operator~=( const Bitset & other );

    // Boolean operations //
    Bitset & operator&( const Bitset & other );
    Bitset & operator|( const Bitset & other );
    Bitset & operator^( const Bitset & other );
    Bitset & operator~( const Bitset & other );

    // Conversions //
    Byteset toByteset() const;
};

#endif
