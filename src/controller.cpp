#include "controller.h"

Controller::Controller() { }

void Controller::HandleInput(bool &running) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
    }
}
