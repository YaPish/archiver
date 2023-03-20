#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

class Controller {
private:


public:
    void    setMetadata( Metadata value );
    Command nextCommand();
};

#endif
