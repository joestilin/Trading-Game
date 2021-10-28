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
        void CalculateExtremes();
        void CalculateRollingMax(int window);
        void CalculateSMA(int window);
        void CalculateVolatility();
        DataParser parser;


};

#endif