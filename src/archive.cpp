#include <iostream>
#include <fstream>
#include <filesystem>

#include "archive.h"

Archive::Archive(
    Version        minVersion,
    CompressMethod defaultCompressMethod,
    EncodeMethod   defaultEncodeMethod ) {
    m_general.minVersion            = minVersion;
    m_general.defaultCompressMethod = defaultCompressMethod;
    m_general.defaultEncodeMethod   = defaultEncodeMethod;
}

Archive::Archive( std::filesystem::path srcGlobalPath ) {

}


void Archive::m_writeGeneral( std::ofstream & outputFile ) {
    std::uint8_t sectionLength;
    switch( m_general.minVersion ) {
        case VERSION_DEV_BETA: sectionLength = 4; break;
    }
    outputFile.put( sectionLength );

    if( m_general.minVersion >= VERSION_DEV_BETA ) {
        outputFile.put( m_general.minVersion );
        outputFile.put( m_general.defaultCompressMethod );
        outputFile.put( m_general.defaultEncodeMethod );
        outputFile.put( m_general.wordSize.to_ulong() );
    }
}

void Archive::m_writeNames( std::ofstream & outputFile, std::filesystem::file_type type ) {
    std::list< std::uint64_t > bitwiseNames = m_catalog.bitwiseNames( type );
    std::uint64_t              nameSize = m_catalog.nameSize( type );

    auto entityIterator = bitwiseNames.begin();
    std::uint64_t delta;

    while( entityIterator != bitwiseNames.end() ) {
        // write delta //
        delta = * entityIterator;
        outputFile.put( delta );

        // write ascii name //
        for( std::uint64_t i = 0; i < delta || entityIterator != bitwiseNames.end(); i++ ) {
            std::advance( entityIterator, 1 );
            outputFile.put( * entityIterator );
        }
    }
}

void Archive::m_writeCatalog( std::ofstream & outputFile ) {
    std::list< std::uint64_t > bitwiseCatalog = m_catalog.bitwiseCatalog();

    std::uint64_t folderNameSize = m_catalog.nameSize( std::filesystem::file_type::directory );
    std::uint64_t fileNameSize   = m_catalog.nameSize( std::filesystem::file_type::regular );

    for( std::uint64_t i : bitwiseCatalog ) {
        outputFile.write( reinterpret_cast< char * >( & i ),
                          i & FOLDER_FLAG ? folderNameSize : fileNameSize );
    }
}

void Archive::m_writeFiles( std::ofstream & outputFile ) {

}


Version Archive::minVersion() const {
    return m_general.minVersion;
}

CompressMethod Archive::defaultCompressMethod() const {
    return m_general.defaultCompressMethod;
}

EncodeMethod Archive::defaultEncodeMethod() const {
    return m_general.defaultEncodeMethod;
}

std::uint8_t Archive::countBytesFolderId() const {

}

std::uint8_t Archive::countBytesFileId() const {

}



void Archive::add( std::filesystem::file_type pathType,
                   std::filesystem::path srcGlobalPath,
                   std::filesystem::path destLocalPath ) {
    // TODO
    m_catalog.add( pathType, srcGlobalPath, destLocalPath );
}

void Archive::remove( std::filesystem::path srcLocalPath ) {
    m_catalog.remove( srcLocalPath );
}

void Archive::move( std::filesystem::path srcLocalPath,
                    std::filesystem::path destLocalPath ) {

}

void Archive::updatePack() {

}

void Archive::pack( std::string           archiveName,
                    std::filesystem::path destGlobalPath ) {
    if( !std::filesystem::is_directory( destGlobalPath ) )
        return;

    std::ofstream outputFile( destGlobalPath / archiveName,
                              std::ios::binary | std::ios::out );
    if ( !outputFile.is_open() )
        return;

    m_writeGeneral( outputFile );

    m_writeCatalog( outputFile );

    m_writeNames( outputFile, std::filesystem::file_type::directory );
    m_writeNames( outputFile, std::filesystem::file_type::regular );

    m_writeFiles( outputFile );

    outputFile.close();
}

void Archive::extract( std::filesystem::path destGlobalPath ) {

}
