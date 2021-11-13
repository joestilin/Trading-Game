#ifndef DATABAR_H
#define DATABAR_H

#include <string>


class DataBar {

    public:
        DataBar();

        std::string date;
        std::string time;
        double open;
        double high;
        double low;
        double close;
        double rolling_high;
        double rolling_low;
        double large_sma;
        double small_sma;
        double volatility;
    
    private:
};

#endif