#ifndef ENDGAME_H
#define ENDGAME_H

#include "tradelog.h"
#include "controller.h"
#include "renderer.h"
#include "state.h"


class EndGame {
    public:
        EndGame();
        void Run(State &state, Controller &controller, Renderer &renderer, 
                TradeLog &tradelog, std::size_t &target_frame_duration);
        void Update();
    
    private:
        Uint32 total_duration{5000}; // the length, in ms, of the end game page display

};

#endif