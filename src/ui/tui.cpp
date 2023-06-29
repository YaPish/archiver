#include <string.h>
#include "tui.h"


void Tui::parseCommand( int argc, char ** argv ) {
    if( strcmp( argv[ 1 ], ENTITY_INIT ) == 0 ) {
        // TODO: init server
    } else if( strcmp( argv[ 1 ], ENTITY_ARCHIVE ) == 0 ) {
               if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_SELECT )      == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_CREATE )      == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_REMOVE )      == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_PREVIEW )     == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_HIDE )        == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_PACK )        == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_EXTRACT )     == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_EDIT_ADD )    == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_EDIT_REMOVE ) == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_ARCHIVE_EDIT_MOVE )   == 0 ) {

        } else {
            // TODO: send error
        }
    } else if( strcmp( argv[ 1 ], ENTITY_FOLDER )  == 0 ) {
               if( strcmp( argv[ 2 ], COMMAND_FOLDER_OPEN )         == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_FOLDER_BACK )         == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_FOLDER_SHOW )         == 0 ) {

        } else {
            // TODO: send error
        }
    } else if( strcmp( argv[ 1 ], ENTITY_FILE )    == 0 ) {
               if( strcmp( argv[ 2 ], COMMAND_FILE_OPEN )           == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_FILE_CLOSE )          == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_FILE_COMPRESS )       == 0 ) {

        } else if( strcmp( argv[ 2 ], COMMAND_FILE_DECOMPRESS )     == 0 ) {

        } else {
            // TODO: send error
        }
    } else {
        // TODO: send error
    }
}

void Tui::showInfo() {

}
