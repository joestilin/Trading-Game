#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "dataframe.h"
#include "tradelog.h"
#include "renderer.h"
#include "controller.h"

class Game {
    public:
        Game();
        
        void Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration);

    private:
        DataFrame *dataframe;
        TradeLog *tradelog;

};

#endif