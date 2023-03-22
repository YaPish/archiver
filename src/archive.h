#ifndef _ARCHIVE_H_
#define _ARCHIVE_H_

class Archive {
private:
    struct GENERAL {
        uint8_t length;
        uint8_t minVersion;

        uint8_t compressionWordMethodId;
        Bitset  wordSize;
    } m_generalInformation;

    struct CATALOGS {
        
    };

public:
    void
};

#endif
