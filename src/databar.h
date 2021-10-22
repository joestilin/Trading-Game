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
        double min_low;     // the lowest low seen so far in the dataframe data vector containing this bar
        double max_high;    // the highest high seen so far in the dataframe data vector containing this bar
        double rolling_high;
        double rolling_low;
    
    private:
};

#endif