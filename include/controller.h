#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL2/SDL.h>
#include <string>


enum Action {BUY, SELL, HOLD};

class Controller {

    public:
        Controller();
        void HandleInput(bool &running, Action &action);
        void HandleLobbyInput(bool &running, bool &selection, std::string &inputText);
};

#endif