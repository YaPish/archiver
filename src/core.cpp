#include <iostream>

#include <sys/stat.h>
#include <string>
#include <cstring>

#include "core.h"


///////////////////////////////////////////////////////////////////////////////
//                                    Fifo                                   //
///////////////////////////////////////////////////////////////////////////////

void Core::m_executeFifo() {
    /*
    // TODO: static cast
    std::uint8_t commandId = m_pipeFifo.get();
    std::uint8_t countArgs = m_pipeFifo.get();
    if( countArgs ) {
        char ** args = new char *[ countArgs ];
        for( std::uint8_t i = 0; i < countArgs; i++ ) {
            std::size_t argSize = m_pipeFifo.get();
            //m_pipeFifo.getline( &args[ i ], argSize );
        }
    }

    // execute command //
    switch( commandId ) {
        default:
            break;
    }

    // TODO: remove args[]
    */
}

void Core::m_clearFifo() {

}

///////////////////////////////////////////////////////////////////////////////
//                                    Core                                   //
///////////////////////////////////////////////////////////////////////////////

Core::Core( void )
    : m_status( CORE_STATUS_NON ) {}

void Core::init( void ) {
    std::filesystem::path pipeFifoPath;

    // TODO: check existing directory
    if( mkfifo( pipeFifoPath.c_str(), 0777 ) ) {
        // TODO: error
    }
    m_pipeFifo.open( pipeFifoPath );

    m_status = CORE_STATUS_AVAILABLE;
}

void Core::update( void ) {
    /*
    std::filesystem::path pipeFifoPath;

    while( m_status == CORE_STATUS_AVAILABLE ) {
        m_pipeFifo.open( pipeFifoPath, std::ios::in );
        if( !m_pipeFifo.is_open() ) {
            // TODO: error
        }

        // TODO: checks by statuses
        m_executeFifo();
        m_clearFifo();
    }
    // TODO: stop server
    */
}

void Core::__exetest( int argc, char ** argv ) {
    if( argc <= 2 ) return;

    if( std::strcmp( argv[ 1 ], "pack" ) == 0 )
        pack( std::filesystem::path( argv[ 2 ] ) );
    else if( std::strcmp( argv[ 1 ], "extract" ) == 0 )
        extract( std::filesystem::path( argv[ 2 ] ) );
    else if( std::strcmp( argv[ 1 ], "compress" ) == 0 )
        compress( std::filesystem::path( argv[ 2 ] ), std::string( argv[ 3 ] ) );
    else if( std::strcmp( argv[ 1 ], "decompress" ) == 0 )
        decompress( std::filesystem::path( argv[ 2 ] ) );
}


///////////////////////////////////////////////////////////////////////////////
//                                   Methods                                 //
///////////////////////////////////////////////////////////////////////////////

void Core::pack( std::filesystem::path srcPath ) {
    m_archive.pack( srcPath );
}

void Core::extract( std::filesystem::path archivePath ) {
    m_archive.extract( archivePath );
}


#define HIDE_PATH_VIEW( __SRC_PATH__, __RESULT__ )              \
    __RESULT__ = __SRC_PATH__;                                  \
    __RESULT__.remove_filename();                               \
    __RESULT__ += "."; __RESULT__ += __SRC_PATH__.filename()

#define SHOW_PATH_VIEW( __SRC_PATH__, __RESULT__ )              \
    __RESULT__ = __SRC_PATH__;                                  \
    __RESULT__.remove_filename();                               \
    std::string __TMP_STR__ = __SRC_PATH__.filename().string(); \
    __TMP_STR__.erase( 0, 1 );                                  \
    __RESULT__ /= __TMP_STR__


void Core::compress( std::filesystem::path srcPath, std::string method ) {
    if( std::filesystem::is_directory( srcPath ) ) return; // TODO: error

    // Hide src path
    std::filesystem::path hiddenPath, shownPath = srcPath;
    HIDE_PATH_VIEW( srcPath, hiddenPath );
    std::filesystem::rename( srcPath, hiddenPath );

    // Touch dest file and open files
    std::fstream src, dest;
    src.open( hiddenPath, std::ios::binary | std::ios::in );
    dest.open( shownPath, std::ios::binary | std::ios::out );
    if( !src.is_open() || !dest.is_open() ) return; // TODO: error

    // Set method signature
    std::uint8_t methodSize = method.size();
    src.put( methodSize );
    src.write( method.c_str(), methodSize );

    // Exe method
    std::string command = "/usr/local/share/yap/Methods/";
    command += ( method + "/./compress " + hiddenPath.c_str() + " " + shownPath.c_str() );
    int methodError = std::system( command.c_str() );
    src.close(); dest.close();
    switch( methodError ) {
        case 0:
            std::filesystem::remove( hiddenPath );
            break;
        default:
            std::filesystem::remove( shownPath );
            std::filesystem::rename( hiddenPath, shownPath );
            break;
    }
}

void Core::decompress( std::filesystem::path srcPath ) {
    if( std::filesystem::is_directory( srcPath ) ) return; // TODO: error

    // Hide src path
    std::filesystem::path hiddenPath, shownPath = srcPath;
    HIDE_PATH_VIEW( srcPath, hiddenPath );
    std::filesystem::rename( srcPath, hiddenPath );

    // Touch dest file and open files
    std::fstream src, dest;
    src.open( hiddenPath, std::ios::binary | std::ios::in );
    dest.open( shownPath, std::ios::binary | std::ios::out );
    if( !src.is_open() || !dest.is_open() ) return; // TODO: error

    // Get method signature
    std::uint8_t methodSize = src.get();
    char *       method     = new char[ methodSize ];
    src.read( method, methodSize );

    // Exe method
    std::string command = "/usr/local/share/yap/Methods/";
    command += ( std::string( method ) + "/./decompress " + hiddenPath.c_str() +
                                                      " " + shownPath.c_str() );
    int methodError = std::system( command.c_str() );

    src.close(); dest.close();
    switch( methodError ) {
        case 0:
            std::filesystem::remove( hiddenPath );
            break;
        default:
            std::filesystem::remove( shownPath );
            std::filesystem::rename( hiddenPath, shownPath );
            break;
    }
    delete[] method;
}
