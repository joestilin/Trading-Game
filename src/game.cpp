
#include "game.h"
#include <SDL2/SDL.h>
#include "trade.h"
#include <iostream>


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
        action = Action::HOLD;
        controller.HandleInput(running, scrolling, action);
        Update(renderer, tradelog);
        renderer.Render(dataframe, tradelog, scrolling);
        SDL_Delay(10);
        std::cout << tradelog.balance << "\n";
    }

}

void Game::Update(Renderer &renderer, TradeLog &tradelog) {
    Trade trade;
    if (scrolling) {
        scroll_position++;
    }
        switch(tradelog.current_position) {
            case FLAT:
                trade.entry_price = dataframe.data[renderer.bars_displayed].close;
                switch (action) {
                    case BUY:
                        trade.direction = Direction::LONG;
                        tradelog.current_position = Direction::LONG;
                    case SELL:
                        trade.direction = Direction::SHORT;
                        tradelog.current_position = Direction:: LONG;
                }
                
            case SHORT:
                switch (action) {
                    case BUY:
                        trade.exit_price = dataframe.data[renderer.bars_displayed].close;
                        trade.profit = trade.shares * (trade.exit_price - trade.entry_price);
                        tradelog.balance += trade.profit;
                        tradelog.current_position = Direction::FLAT;
                    case SELL:
                        return;
                }
            
            case LONG:
                switch(action) {
                    case BUY:
                        return;
                    case SELL:
                        trade.exit_price = dataframe.data[renderer.bars_displayed].close;
                        trade.profit = trade.shares * (trade.entry_price - trade.exit_price);
                        tradelog.balance += trade.profit;
                        tradelog.current_position = Direction::FLAT;
                }
        }   
}