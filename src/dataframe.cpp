#include "dataframe.h"
#include <iostream>
#include <cmath>

DataFrame::DataFrame() { }

void DataFrame::LoadData() {
    parser.ParseData(data);
    n_bars = data.size();
    CalculateExtremes();
    CalculateRollingMax(25);
    CalculateSMA(100);
    CalculateVolatility();
    std::cout << volatility << "\n";
}

void DataFrame::PrintData() {
    for (auto databar : data) {
        std::cout << databar.date << " " << databar.open << " " 
        << databar.high << " " << databar.low << " " << databar.close << "\n";
    }
}

// Function to calculate attributes of the data including indicators
void DataFrame::CalculateExtremes() {
    max_high = 0;
    min_low = 1000000; // some large number

     for (auto &bar : data) {
         if (bar.high > max_high) {
             max_high = bar.high;
             bar.max_high = bar.high;
         }
         else{ 
             bar.max_high = max_high;
         }

         if (bar.low  < min_low) {
             min_low = bar.low;
             bar.min_low = bar.low;
         }
         else {
             bar.min_low = min_low;
         }
     }

     std::cout << "calculated some stuff\n";
}

// inefficient method to calculate rolling max
void DataFrame::CalculateRollingMax(int window) {
    double max = 0;
    double min = 1000000;
    for (std::vector<DataBar>::size_type i = 0; i !=data.size() - window; i++) {
        max = data[i].high;
        min = data[i].low;
        for (std::vector<DataBar>::size_type j = i; j != i + window; j++) {
            if (data[j].high > max) {
                max = data[j].high;
            }
            if (data[j].low < min) {
                min = data[j].low;
            }
        }
        data[i].rolling_high = max;
        data[i].rolling_low = min;
    }

}

void DataFrame::CalculateSMA(int window) {
    double sum = 0;
    for (std::vector<DataBar>::size_type i = 0; i != data.size(); i++) {
        sum += data[i].close;
        if (i > window) {
            sum -= data[i - window].close;
            data[i].sma = sum / window;
        }
        else 
        {
            data[i].sma = sum / (i + 1);
        }

    }
}

void DataFrame::CalculateVolatility() {
    double sum = 0;
    double mean = 0;
    double sum_squares = 0;

    for (auto &bar : data) {
        sum += bar.close;
    }

    mean = sum / n_bars;

    for (auto &bar : data) {
        sum_squares += std::pow(bar.close - mean, 2);
    }

    volatility = std::pow(sum_squares / n_bars, 0.5);
}
