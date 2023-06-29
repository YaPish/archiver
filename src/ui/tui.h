#ifndef _TUI_H_
#define _TUI_H_


#define ENTITY_INIT                 "init"
#define ENTITY_ARCHIVE              "archive"
#define ENTITY_FOLDER               "folder"
#define ENTITY_FILE                 "file"


#define COMMAND_ARCHIVE_SELECT      "select"      // ( 1 args ) srcGlobalPath
#define COMMAND_ARCHIVE_CREATE      "create"      // ( 1 args ) destGlobalPath
#define COMMAND_ARCHIVE_REMOVE      "remove"      // ( 1 args ) srcGlobalPath
#define COMMAND_ARCHIVE_PREVIEW     "preview"     // ( 1 args ) srcGlobalPath
#define COMMAND_ARCHIVE_HIDE        "hide"        // ( 1 args ) srcGlobalPath
#define COMMAND_ARCHIVE_PACK        "pack"        // ( 1 args ) srcGlobalPath
#define COMMAND_ARCHIVE_EXTRACT     "extract"     // ( 2 args ) srcGlobalPath,
                                                  //            destGlobalPath

#define COMMAND_ARCHIVE_EDIT_ADD    "add"         // ( 2 args ) srcGlobalPath,
                                                  //            destLocalPath
#define COMMAND_ARCHIVE_EDIT_REMOVE "remove"      // ( 1 args ) srcLocalPath
#define COMMAND_ARCHIVE_EDIT_MOVE   "move"        // ( 2 args ) srcLocalPath,
                                                  //            destLocalPath

#define COMMAND_FOLDER_OPEN         "open"        // ( 1 args ) srcLocalPath
#define COMMAND_FOLDER_BACK         "back"        // ( 0 args )
#define COMMAND_FOLDER_SHOW         "show"        // ( 0 args )


#define COMMAND_FILE_OPEN           "open"        // ( 1 args ) srcLocalPath
#define COMMAND_FILE_CLOSE          "close"       // ( 1 args ) srcLocalPath
#define COMMAND_FILE_COMPRESS       "compress"    // ( 2 args ) srcLocalPath
                                                  //            compressMethod
#define COMMAND_FILE_DECOMPRESS     "decompress"  // ( 1 args ) srcLocalPath


class Tui {
public:
    Tui() = default;

    void parseCommand( int argc, char ** argv );
    void showInfo();
};

#endif
