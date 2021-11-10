#include "dataframe.h"
#include <iostream>
#include <cmath>

DataFrame::DataFrame() { }

void DataFrame::LoadData() {
    parser.ParseData(data);
    n_bars = data.size();
    CalculateSMA(100);
    CalculateVolatility(100);
}

void DataFrame::PrintData() {
    for (auto databar : data) {
        std::cout << databar.date << " " << databar.open << " " 
        << databar.high << " " << databar.low << " " << databar.close << "\n";
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

void DataFrame::CalculateVolatility(int window) {
    double sum = 0;
    double mean = 0;
    double sum_squares = 0;

    /*
    for (std::vector<DataBar>::size_type i = 0; i != data.size(); i++) {
        sum += data[i].close;
        if (i > window) {
            sum -= data[i - window].close;
            mean = sum / window;
            for (std::vector<DataBar>::size_type j = i - window; j != i; j++) {
                sum_squares += std::pow(data[j].close - mean, 2);
            }
            data[i].volatility = std::pow(sum_squares / window, 0.5);
            sum_squares = 0;
        }
    }
    */

    for (auto &bar : data) {
        sum += bar.close;
    }

    mean = sum / n_bars;

    for (auto &bar : data) {
        sum_squares += std::pow(bar.close - mean, 2);
    }

    volatility = std::pow(sum_squares / n_bars, 0.5);
    
}
