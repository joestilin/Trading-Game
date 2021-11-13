#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include "databar.h"
#include "dataparser.h"

class DataFrame {

    public:
        DataFrame();
        void LoadData();
        void PrintData();
        
        std::vector<DataBar> data;

        double max_high;
        double min_low;
        std::size_t n_bars;
        double volatility;
        
    private:
        void CalculateLargeSMA(int window);
        void CalculateSmallSMA(int window);
        void CalculateRollingVolatility(int window);
        void CalculateVolatility();
        void CalculateRollingExtremes(int window);
        DataParser parser;


};

#endif