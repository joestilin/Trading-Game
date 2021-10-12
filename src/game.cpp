
#include "game.h"
#include <SDL2/SDL.h>


Game::Game() {

    // create financial dataframe from file
    dataframe.LoadData();

}

void Game::Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration) {

    // a test
    // dataframe.PrintData();

    // game loop
    while (running) {
        scrolling = false;
        controller.HandleInput(running, scrolling);
        Update();
        renderer.Render(dataframe, scroll_position);
        SDL_Delay(10);
    }

}

void Game::Update() {
    if (scrolling) {
        scroll_position++;
    }
}