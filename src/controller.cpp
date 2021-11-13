#include "controller.h"

Controller::Controller() { }

void Controller::HandleInput(bool &running, Action &action) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
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

void Controller::HandleLobbyInput(bool &running, bool &selection, bool &random_selection, std::string &inputText) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                // handle backspace
                if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 ) {
                    inputText.pop_back(); 
                    // renderText = true;
                }
                // handle copy
                else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                    SDL_SetClipboardText(inputText.c_str());
                }
                // handle paste
                else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                    inputText = SDL_GetClipboardText();
                    // renderText = true;
                }
                // handle enter
                else if (e.key.keysym.sym == SDLK_RETURN) {
                    selection = true;
                }
                // handle right arrow
                else if (e.key.keysym.sym == SDLK_RIGHT) {
                    random_selection = true;
                }
            break;
            //Special text input event
            case SDL_TEXTINPUT:
                //Not copy or pasting. Also, ignore spaces
                if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) || e.text.text[0] == ' ') )
                    {
                        //Append character
                        inputText += e.text.text;
                        //renderText = true;
                    }
            break; 
        }
    }
}