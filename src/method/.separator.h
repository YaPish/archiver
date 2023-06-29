#ifndef _SEPARATOR_H_
#define _SEPARATOR_H_

#include <fstream>
#include <list>

#include "../def.h"

class Separator {
    private:
        std::ifstream &           m_stream;
        size_t                    m_blockSize;

    public:
        Separator( std::ifstream & stream );

        void   setBlockSize( size_t value );
        size_t getBlockSize() const;

        std::list< std::uint8_t > getBlock();
};

#endif
