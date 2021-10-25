#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL2/SDL.h>


enum Action {BUY, SELL, HOLD};

class Controller {

    public:
        Controller();
        void HandleInput(bool &running, bool &scrolling, Action &action);

};


#endif