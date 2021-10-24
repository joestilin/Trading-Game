
#include "game.h"
#include <SDL2/SDL.h>
#include "trade.h"


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
        buying = false;
        selling = false;
        controller.HandleInput(running, scrolling, buying, selling);
        Update(renderer, tradelog);
        renderer.Render(dataframe, tradelog, scrolling);
        SDL_Delay(10);
    }

}

void Game::Update(Renderer &renderer, TradeLog &tradelog) {
    if (scrolling) {
        scroll_position++;
    }
    if (buying) {
        switch(tradelog.current_position) {
            case FLAT:
                Trade trade;
                trade.entry_price = dataframe.data[renderer.bars_displayed].close;
                trade.direction = Direction::LONG;
            case SHORT:
                // TODO close out the current short position.
        }
    }
        
    if (selling) {
        // TODO: close trade if long, create new trade if short

    }
}