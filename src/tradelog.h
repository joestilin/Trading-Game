#ifndef TRADELOG_H
#define TRADELOG_H

#include "trade.h"


class TradeLog {
    public:
        TradeLog();
        std::vector<Trade> trades;
        double balance;
        Direction current_position{Direction::FLAT};
};


#endif