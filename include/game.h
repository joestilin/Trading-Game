#ifndef GAME_H
#define GAME_H

#include "symbol.h"
#include "tradelog.h"
#include "endgame.h"
#include "renderer.h"
#include "controller.h"
#include "lobby.h"
#include "chart.h"
#include "state.h"

class Game {
    public:
        Game();
        void Run();
        Symbol currentSymbol;
        TradeLog tradelog;
        State state;
        bool running;

};

#endif