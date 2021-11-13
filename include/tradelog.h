#ifndef TRADELOG_H
#define TRADELOG_H

#include <vector>
#include "trade.h"


class TradeLog {
    public:
        TradeLog();
        std::vector<Trade> trades;
        double balance{10000};
        Direction current_position{Direction::FLAT};
};


#endif