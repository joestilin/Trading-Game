#ifndef CHART_H
#define CHART_H

#include <SDL2/SDL.h>
#include "dataframe.h"
#include "tradelog.h"
#include "renderer.h"
#include "controller.h"
#include "trade.h"
#include "symbol.h"

class Chart {
    public:
        Chart();
        void Run(bool &running, Controller &controller, Renderer &renderer, Symbol &currentSymbol, std::size_t target_frame_duration);
        void Update(bool &running);
        double getBalance();
        bool complete;

    private:
        void OpenTrade();
        void CloseLongTrade();
        void CloseShortTrade();
        void UpdateOpenTradeProfit();

        DataFrame dataframe;
        TradeLog tradelog;

        //std::size_t scroll_position = 10;
        std::size_t current_bar{10};
        Action action;
        bool scrolling = false;
        bool buying = false;
        bool selling = false;
        bool long_position = false;
        bool short_position = false;

};

#endif