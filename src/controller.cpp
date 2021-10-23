#include "controller.h"

Controller::Controller() { }

void Controller::HandleInput(bool &running, bool &scrolling, bool &buying, bool &selling) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                running = false;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        scrolling = true;
                    case SDLK_UP:
                        buying = true;
                    case SDLK_DOWN:
                        selling = true;
                }
         }
        
    }
}
