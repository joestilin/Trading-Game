#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "dataframe.h"
#include "tradelog.h"
#include "renderer.h"
#include "controller.h"

enum Action {BUY, SELL};

class Game {
    public:
        Game();
        void Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration);
        void Update(Renderer &renderer, TradeLog &tradelog);

    private:
        DataFrame dataframe;
        TradeLog tradelog;

        // Percentage of maximum scroll
        std::size_t scroll_position = 10;
        bool running = true;
        Action action;
        bool scrolling = false;
        bool buying = false;
        bool selling = false;
        bool long_position = false;
        bool short_position = false;

};

#endif