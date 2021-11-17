#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SDL2/SDL.h>
#include <string>
#include "state.h"


enum Action {BUY, SELL, HOLD};

class Controller {

    public:
        Controller();
        // monitor input from user while chart runs and change state and action enums accordingly
        void HandleChartInput(State &state, Action &action);
        // monitor input from user while the lobby runs and change state, selection, random_selection, and update inputText
        void HandleLobbyInput(State &state, bool &selection, bool &random_selection, std::string &inputText);
        // monitor input from user and change state accordingly
        void HandleEndGameInput(State &state);
};

#endif