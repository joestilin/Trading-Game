#ifndef CHART_H
#define CHART_H

#include <iostream>
#include <SDL2/SDL.h>
#include "dataframe.h"
#include "tradelog.h"
#include "renderer.h"
#include "controller.h"
#include "trade.h"
#include "symbol.h"
#include "state.h"

class Chart {
    public:
        Chart();
        
        void Run(State &state, Controller &controller, Renderer &renderer, 
                TradeLog &tradelog, Symbol &currentSymbol, 
                std::size_t target_frame_duration);
 
        void Update(State &state, TradeLog &tradelog);

        // whether the chart has reached its final bar or not
        bool complete;

    private:
        // open a new trade
        void OpenTrade(TradeLog &tradelog);
        // close a long trade
        void CloseLongTrade(TradeLog &tradelog);
        // close a short trade
        void CloseShortTrade(TradeLog &tradelog);
        // update the profit value of an open trade
        void UpdateOpenTradeProfit(TradeLog &tradelog);

        DataFrame dataframe;

        // the index of the current bar in the chart.
        std::size_t current_bar{10};
        Action action;
        bool scrolling = false;
        bool buying = false;
        bool selling = false;
        bool long_position = false;
        bool short_position = false;

};

#endif