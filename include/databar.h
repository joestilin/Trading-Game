#ifndef DATABAR_H
#define DATABAR_H

#include <string>


class DataBar {

    public:
        // Encapsulates data for a time unit (bar) of financial data
        DataBar();

        std::string date;
        std::string time;
        double open;
        double high;
        double low;
        double close;
        double rolling_high;
        double rolling_low;
        double sma;
        double volatility;
    
    private:
};

#endif