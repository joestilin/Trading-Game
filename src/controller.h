#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL2/SDL.h>

class Controller {

    public:
        Controller();
        void HandleInput(bool &running, bool &scrolling, bool &buying, bool &selling);

};



#endif