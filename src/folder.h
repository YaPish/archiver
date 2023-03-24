#ifndef _FOLDER_H_
#define _FOLDER_H_

class Folder {
private:
    std::uint64_t         m_id;

    std::list< Folder * > m_folders;
    Folder *              m_backFolder;

    std::list< File * >   m_files;

public:
    Folder(
        std::string name
    );

    std::string name;

    Byteset getArchivedView();

    struct files {
        std::size_t count() const;

        void add( File src );
        void remove( File * src );

        File * get( std::string name );
        File * get( std::uint64_t id );
    };

    struct folders {
        std::size_t count() const;

        void add( Folder src );
        void remove( Folder * src );

        Folder * get( std::string name );
        Folder * get( std::uint64_t id );

        Folder * back();
    };
};



Folder test;
test.folders.add

#endif
