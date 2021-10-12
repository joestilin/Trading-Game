#include "controller.h"

Controller::Controller() { }

void Controller::HandleInput(bool &running, bool &scrolling) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                running = false;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        scrolling = true;
                }
         }
        
    }
}
