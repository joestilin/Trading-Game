#ifndef GAME_H
#define GAME_H

#include "symbol.h"
#include "tradelog.h"

class Game {
    public:
        Game();
        void Run();
        Symbol currentSymbol;
        TradeLog tradelog;
        bool running;

};

#endif