#ifndef TRADELOG_H
#define TRADELOG_H

#include <vector>
#include "trade.h"


class TradeLog {
    public:
        TradeLog();
        std::vector<Trade> trades;
        double balance{100000};
        double position_percent{1.0};
        double winning_goal{1000000};
        Direction current_position{Direction::FLAT};
};
#endif