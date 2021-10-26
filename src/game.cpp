
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
        
        Update(renderer);
        renderer.Render(dataframe, tradelog, scrolling);
        if (action == Action::BUY) {
            std::cout << tradelog.balance << " " << tradelog.trades.size() << "\n";
        }
        if (action == Action::SELL) {
            std::cout << tradelog.balance << " " << tradelog.trades.size() << "\n";
        }
        SDL_Delay(10);
    }
}

void Game::Update(Renderer &renderer) {
    if (scrolling) {
        scroll_position++;
    }
    if (action != HOLD){
        switch(tradelog.current_position) { 
            case FLAT:
                OpenTrade(renderer);
                break;
            case SHORT:
                CloseShortTrade(renderer);
                break;
            case LONG:
                CloseLongTrade(renderer);
                break;
        }
    }   
}

void Game::OpenTrade(Renderer &renderer) {
    Trade trade;
    trade.entry_price = dataframe.data[renderer.bars_displayed].close;
    switch (action) {
        case BUY:
            trade.direction = Direction::LONG;
            tradelog.current_position = Direction::LONG;
            break;
        case SELL:
            trade.direction = Direction::SHORT;
            tradelog.current_position = Direction::SHORT;
            break;
    }
    tradelog.trades.push_back(trade);
}

void Game::CloseShortTrade(Renderer &renderer) {
    Trade& trade = tradelog.trades[0];
        switch (action) {
            case BUY:
                trade.exit_price = dataframe.data[renderer.bars_displayed].close;
                trade.profit = trade.shares * (trade.entry_price - trade.exit_price);
                tradelog.balance += trade.profit;
                tradelog.current_position = Direction::FLAT;
                break;
            case SELL:
                // do nothing if already short and trying to sell
                break;
        }
}

void Game::CloseLongTrade(Renderer &renderer) {
    Trade& trade = tradelog.trades[0];
    switch(action) {
        case BUY:
            // do nothing if already long and trying to buy
            break;
        case SELL:
            trade.exit_price = dataframe.data[renderer.bars_displayed].close;
            trade.profit = trade.shares * (trade.exit_price - trade.entry_price);
            tradelog.balance += trade.profit;
            tradelog.current_position = Direction::FLAT;
        break;
    }
}