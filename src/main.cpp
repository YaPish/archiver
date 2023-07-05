#include "def.h"
#include "core.h"

#define ARG_COUNT   ( argc - 2 )
#define ARG_COMMAND argv[ 1 ]

#define ARG_1       argv[ 2 ]
#define ARG_2       argv[ 3 ]
#define ARG_3       argv[ 4 ]

int main( int argc, char ** argv ) {
    g_error = ERROR_NON;
    if( ARG_COUNT <= 0 ) {
        MSG_ERR( "No command", ERROR_COMMAND );
    }
    if( g_error != ERROR_NON ) return g_error;

    Core archiveCore;
    if( std::string( ARG_COMMAND ) == COMMANDS[ 0 ].name ) {        /* Pack       */
        if( ARG_COUNT != COMMANDS[ 0 ].countArgs ) {
            MSG_ERR( "Invalid quantity arguments", ERROR_COUNT );
        }
        if( g_error != ERROR_NON ) return g_error;
        archiveCore.pack( ARG_1 );
    } else if( std::string( ARG_COMMAND ) == COMMANDS[ 1 ].name ) { /* Extract    */
        if( ARG_COUNT != COMMANDS[ 1 ].countArgs ) {
            MSG_ERR( "Invalid quantity arguments", ERROR_COUNT );
        }
        if( g_error != ERROR_NON ) return g_error;
        archiveCore.extract( ARG_1 );
    } else if( std::string( ARG_COMMAND ) == COMMANDS[ 2 ].name ) { /* Compress   */
        if( ARG_COUNT != COMMANDS[ 2 ].countArgs ) {
            MSG_ERR( "Invalid quantity arguments", ERROR_COUNT );
        }
        if( g_error != ERROR_NON ) return g_error;
        archiveCore.compress( ARG_2, ARG_1 );
    } else if( std::string( ARG_COMMAND ) == COMMANDS[ 3 ].name ) { /* Decompress */
        if( ARG_COUNT != COMMANDS[ 3 ].countArgs ) {
            MSG_ERR( "Invalid quantity arguments", ERROR_COUNT );
        }
        if( g_error != ERROR_NON ) return g_error;
        archiveCore.decompress( ARG_1 );
    } else MSG_ERR( "Invalid command", ERROR_COMMAND );

    return g_error;
}
