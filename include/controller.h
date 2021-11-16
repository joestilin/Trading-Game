#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL2/SDL.h>
#include <string>
#include "state.h"


enum Action {BUY, SELL, HOLD};

class Controller {

    public:
        Controller();
        void HandleInput(State &state, Action &action);
        void HandleLobbyInput(State &state, bool &selection, bool &random_selection, std::string &inputText);
        void HandleEndGameInput(State &state);
};

#endif