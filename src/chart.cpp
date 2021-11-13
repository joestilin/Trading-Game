
#include "chart.h"
#include <SDL2/SDL.h>
#include "trade.h"
#include <iostream>


Chart::Chart() { 
    // create financial dataframe from file
    dataframe.LoadData();
}

void Chart::Run(bool &running, Controller &controller, Renderer &renderer, Symbol &currentSymbol, std::size_t target_frame_duration) {

    // timing
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    // chart loop
    while (running) {
        frame_start = SDL_GetTicks();

        scrolling = false;
        action = Action::HOLD;
        controller.HandleInput(running, action);
        Update(running);
        renderer.RenderChart(dataframe, tradelog, current_bar, currentSymbol);
        
        frame_end = SDL_GetTicks();
        frame_count++;
        frame_duration = frame_end - frame_start;

        // calculate frames per second
        if (frame_end - title_timestamp > 1000) {
            renderer.UpdateWindow_Title(frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // throttle the loop to target frame rate
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Chart::Update(bool &running) {

    current_bar++;

    // end the chart when scrolling reaches the last bar in the dataset
    if (current_bar == dataframe.n_bars) {
        complete = true;
    }

    // end the entire game if the player's balance reaches 0
    if (tradelog.balance <= 0) {
        running = false;
    }

    switch (action) {
        case HOLD:
            if (tradelog.trades.size() > 0 && tradelog.trades.back().status == OPEN) {
                UpdateOpenTradeProfit();
            }
            else { }
            break;
    }

    if (action != HOLD){
        switch(tradelog.current_position) { 
            case FLAT:
                OpenTrade();
                break;
            case SHORT:
                CloseShortTrade();
                break;
            case LONG:
                CloseLongTrade();
                break;
        }
    }   
}

double Chart::getBalance() {
    
}

void Chart::OpenTrade() {
    Trade trade;
    trade.entry_price = dataframe.data[current_bar].close;
    switch (action) {
        case BUY:
            trade.direction = Direction::LONG;
            trade.index = current_bar;
            trade.status = Status::OPEN;
            tradelog.current_position = Direction::LONG;
            break;
        case SELL:
            trade.direction = Direction::SHORT;
            trade.index = current_bar;
            trade.status = Status::OPEN;
            tradelog.current_position = Direction::SHORT;
            break;
    }
    tradelog.trades.push_back(trade);
}

void Chart::CloseShortTrade() {
    Trade& trade = tradelog.trades.back();
        switch (action) {
            case BUY:
                trade.exit_price = dataframe.data[current_bar].close;
                trade.profit = trade.shares * (trade.entry_price - trade.exit_price);
                trade.status = Status::CLOSED;
                tradelog.balance += trade.profit;
                tradelog.current_position = Direction::FLAT;
                break;
            case SELL:
                // do nothing if already short and trying to sell
                break;
        }
}

void Chart::CloseLongTrade() {
    Trade& trade = tradelog.trades.back();
    switch(action) {
        case BUY:
            // do nothing if already long and trying to buy
            break;
        case SELL:
            trade.exit_price = dataframe.data[current_bar].close;
            trade.profit = trade.shares * (trade.exit_price - trade.entry_price);
            trade.status = Status::CLOSED;
            tradelog.balance += trade.profit;
            tradelog.current_position = Direction::FLAT;
        break;
    }
}

// TODO: switch for short and long cases
void Chart::UpdateOpenTradeProfit() {
    Trade& trade = tradelog.trades.back();
    trade.profit = dataframe.data[current_bar].close - trade.entry_price;
}