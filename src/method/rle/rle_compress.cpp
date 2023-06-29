#include "rle.h"

int main( int args, char ** argv ) {
    // TODO: create errors
    if( args != 3 ) return -1;

    std::filesystem::path src  = argv[ 1 ];
    std::filesystem::path dest = argv[ 2 ];

    std::fstream srcStream, destStream;
    srcStream.open( src, std::ios::binary | std::ios::in );
    destStream.open( dest, std::ios::binary | std::ios::out );
    if( !srcStream.is_open() || !destStream.is_open() ) {
        return -2;
    }

    RleStatus status = RLE_STATUS_NON;

    std::uint8_t * buffer       = new std::uint8_t[ BUFFER_SIZE ];
    std::uint8_t * vacatedBytes = new std::uint8_t[ MAX_ROW_BYTES ];

    std::uint8_t byteId = 0; // max 128 //

    vacatedBytes[ byteId ] = srcStream.get();

    while( !srcStream.eof() && srcStream.good() ) {
        srcStream.read( reinterpret_cast< char * >( buffer ), BUFFER_SIZE );

        for( std::size_t i = 0; i < srcStream.gcount(); i++ ) {
            switch( status ) {
                case RLE_STATUS_SINGLE:
                if( vacatedBytes[ byteId ] == buffer[ i ] &&
                    byteId < MAX_ROW_BYTES                &&
                    i != srcStream.gcount() - 1 ) {
                    vacatedBytes[ ++byteId ] = buffer[ i ];
                } else {
                    if( i == srcStream.gcount() - 1 )
                        vacatedBytes[ ++byteId ] = buffer[ i ];

                    if( destStream.good() ) {
                        destStream.put( ( byteId + 1 ) | status );
                        destStream.put( vacatedBytes[ 0 ] );
                    }

                    byteId = 0;
                    vacatedBytes[ byteId ] = buffer[ i ];
                    status = RLE_STATUS_NON;
                }
                break;

                case RLE_STATUS_MULTIPLE:
                if( vacatedBytes[ byteId ] != buffer[ i ] &&
                    byteId < MAX_ROW_BYTES                &&
                    i != srcStream.gcount() - 1 ) {
                    vacatedBytes[ ++byteId ] = buffer[ i ];
                } else {
                    if( i == srcStream.gcount() - 1 )
                        vacatedBytes[ ++byteId ] = buffer[ i ];

                    if( destStream.good() ) {
                        destStream.put( ( byteId + 1 ) | status );
                        destStream.write( reinterpret_cast< char * >( vacatedBytes ),
                                    byteId + 1 );
                    }

                    byteId = 0;
                    vacatedBytes[ byteId ] = buffer[ i ];
                    status = RLE_STATUS_NON;
                }
                break;

                case RLE_STATUS_NON:
                status = ( vacatedBytes[ byteId ] == buffer[ i ]
                       ? RLE_STATUS_SINGLE : RLE_STATUS_MULTIPLE );
                vacatedBytes[ ++byteId ] = buffer[ i ]; // so have two bytes //
                break;
            }
        }
    }

    srcStream.close();
    destStream.close();

    return 0;
}
