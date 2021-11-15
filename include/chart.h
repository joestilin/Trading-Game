#ifndef CHART_H
#define CHART_H

#include <SDL2/SDL.h>
#include "dataframe.h"
#include "tradelog.h"
#include "renderer.h"
#include "controller.h"
#include "trade.h"
#include "symbol.h"
#include "tradelog.h"

class Chart {
    public:
        Chart();
        void Run(bool &running, Controller &controller, Renderer &renderer, 
                TradeLog &tradelog, Symbol &currentSymbol, 
                std::size_t target_frame_duration);
        void Update(bool &running, TradeLog &tradelog);
        bool complete;

    private:
        void OpenTrade(TradeLog &tradelog);
        void CloseLongTrade(TradeLog &tradelog);
        void CloseShortTrade(TradeLog &tradelog);
        void UpdateOpenTradeProfit(TradeLog &tradelog);

        DataFrame dataframe;

        std::size_t current_bar{10};
        Action action;
        bool scrolling = false;
        bool buying = false;
        bool selling = false;
        bool long_position = false;
        bool short_position = false;

};

#endif