#include "controller.h"

Controller::Controller() { }

void Controller::HandleInput(bool &running, bool &scrolling, Action &action) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_RIGHT:
                        scrolling = true;
                        break;
                    case SDLK_UP:
                        action = Action::BUY;
                        break;
                    case SDLK_DOWN:
                        action = Action::SELL;
                        break;
                }
                break;
         }
        
    }
}
