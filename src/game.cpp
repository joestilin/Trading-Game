
#include "game.h"
#include <SDL2/SDL.h>


Game::Game() {

    // create financial dataframe from file
    dataframe.LoadData();

}

void Game::Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration) {

    bool running = true;

    // a test
    dataframe.PrintData();

    // game loop
    while (running) {
        controller.HandleInput(running);
        renderer.Render();
        SDL_Delay(10);

    }

}