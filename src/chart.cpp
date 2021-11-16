#include "chart.h"

Chart::Chart() { 
    // create financial dataframe from data file
    dataframe.LoadData();
}

void Chart::Run(State &state, Controller &controller, Renderer &renderer, 
                TradeLog &tradelog, Symbol &currentSymbol,
                std::size_t target_frame_duration) {

    // timing
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    complete = false;

    // chart loop
    while (state == RUNNING && !complete) {
        frame_start = SDL_GetTicks();

        scrolling = false;
        action = Action::HOLD;
        controller.HandleInput(state, action);
        Update(state, tradelog);
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

void Chart::Update(State &state, TradeLog &tradelog) {

    // scroll by one bar each frame
    current_bar++;

    // end the chart when scrolling reaches end
    if (current_bar == dataframe.n_bars) {
        complete = true;
        // close the open trade if there is one and take the profit
        if (tradelog.trades.size() > 0 && tradelog.trades.back().status == OPEN) {
            Trade& trade = tradelog.trades.back();
            trade.status = Status::CLOSED;
            tradelog.balance += trade.profit;
            tradelog.current_position = Direction::FLAT;
        } 
    }

    // display losing page if player's balance falls below zero
    if (tradelog.balance <= 0) {
        std::cout << "You lose!" << std::endl;
        state = LOSE;
    }

    // display winning page if player achieves goal
    if (tradelog.balance >= tradelog.winning_goal) {
        std::cout << "You won!" << std::endl;
        state = WIN;
    }

    // update the open trade profit if there is one
    switch (action) {
        case HOLD:
            if (tradelog.trades.size() > 0 && tradelog.trades.back().status == OPEN) {
                UpdateOpenTradeProfit(tradelog);
            }
            else { 
                // no trades open, do nothing
                 }
            break;
    }

    // handle player buying or selling
    if (action != HOLD){
        switch(tradelog.current_position) { 
            case FLAT:
                OpenTrade(tradelog);
                break;
            case SHORT:
                CloseShortTrade(tradelog);
                break;
            case LONG:
                CloseLongTrade(tradelog);
                break;
        }
    }   
}

void Chart::OpenTrade(TradeLog &tradelog) {
    Trade trade;
    trade.entry_price = dataframe.data[current_bar].close;
    switch (action) {
        case BUY:
            // new long trade
            trade.direction = Direction::LONG;
            trade.index = current_bar;
            trade.status = Status::OPEN;
            tradelog.current_position = Direction::LONG;
            trade.amount = tradelog.position_percent * tradelog.balance / trade.entry_price;
            break;
        case SELL:
            // new short trade
            trade.direction = Direction::SHORT;
            trade.index = current_bar;
            trade.status = Status::OPEN;
            tradelog.current_position = Direction::SHORT;
            trade.amount = tradelog.position_percent * tradelog.balance / trade.entry_price;
            break;
    }
    // push the new trade onto the tradelog trades vector
    tradelog.trades.push_back(trade);
}

void Chart::CloseShortTrade(TradeLog &tradelog) {
    Trade& trade = tradelog.trades.back();
        switch (action) {
            case BUY:
                // close short trade when player buys
                trade.exit_price = dataframe.data[current_bar].close;
                trade.profit = trade.amount * (trade.entry_price - trade.exit_price);
                trade.status = Status::CLOSED;
                tradelog.balance += trade.profit;
                tradelog.current_position = Direction::FLAT;
                break;
            case SELL:
                // do nothing if already short and trying to sell
                break;
        }
}

void Chart::CloseLongTrade(TradeLog &tradelog) {
    Trade& trade = tradelog.trades.back();
    switch(action) {
        case BUY:
            // do nothing if already long and trying to buy
            break;
        case SELL:
            // close long trade when player sells
            trade.exit_price = dataframe.data[current_bar].close;
            trade.profit = trade.amount * (trade.exit_price - trade.entry_price);
            trade.status = Status::CLOSED;
            tradelog.balance += trade.profit;
            tradelog.current_position = Direction::FLAT;
        break;
    }
}

void Chart::UpdateOpenTradeProfit(TradeLog &tradelog) {
    Trade& trade = tradelog.trades.back();
    switch (tradelog.current_position) {
        case LONG:
            // profit is positive when long and price went up
            trade.profit = trade.amount * (dataframe.data[current_bar].close - trade.entry_price);
            break;
        case SHORT:
            // profit if positive when short and price went down
            trade.profit = trade.amount * (trade.entry_price - dataframe.data[current_bar].close);
    }
}