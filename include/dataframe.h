#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include "databar.h"
#include "dataparser.h"

class DataFrame {

    public:
        DataFrame();

        // load financial data from a .csv file
        void LoadData();

        // helpful test function
        void PrintData();
        
        std::vector<DataBar> data;  // vector of DataBars 
        std::size_t n_bars;         // the number of bars in this dataframe
        double volatility;          // the volatility of this dataframe
        
    private:
        // calculate the simple moving average at each bar
        void CalculateSMA(int window);

        // calculate the rolling volatility at each bar
        void CalculateRollingVolatility(int window);

        // calculate the volatility of the entire dataframe
        void CalculateVolatility();

        // calculate the higheset high and lowest low trailing the current bar by window
        void CalculateRollingExtremes(int window);

        // handles parsing data from a .csv file
        DataParser parser;


};

#endif