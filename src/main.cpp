#include "core.h"

int main( int args, char ** argv ) {
    g_error = ERROR_NON;

    Core archiveCore;
    archiveCore.__exetest( args, argv );

    return g_error;
}
