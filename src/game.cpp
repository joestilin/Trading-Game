
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
        controller.HandleInput(running, scrolling, buying, selling);
        Update(renderer);
        renderer.Render(dataframe, tradelog, scrolling);
        SDL_Delay(10);
    }

}

void Game::Update(Renderer &renderer) {
    if (scrolling) {
        scroll_position++;
    }
    if (buying) {
        // TODO: close trade if short, create new trade if long
    }
    if (selling) {
        // TODO: close trade if long, create new trade if short

    }
}