#ifndef GAME_H
#define GAME_H

#include "dataframe.h"
#include "tradelog.h"

class Game {
    public:
        Game();
        
        void Run();

    private:
        DataFrame dataframe;
        TradeLog tradelog;

};

#endif