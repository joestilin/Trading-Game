#ifndef LOBBY_H
#define LOBBY_H

#include "controller.h"
#include "renderer.h"

class Lobby {
    public:

    Lobby();
    void Run(Controller &controller, Renderer &renderer, std::size_t &target_frame_duration);
    void Update();
    bool getState();

    private:
    bool running = true;
    bool chose = false;
};



#endif