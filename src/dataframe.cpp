#include "dataframe.h"
#include <iostream>
#include <cmath>

DataFrame::DataFrame() { }

void DataFrame::LoadData() {
    parser.ParseData(data);
    n_bars = data.size();
    CalculateSMA(100);
    CalculateRollingVolatility(100);
    CalculateVolatility();
    CalculateRollingExtremes(200);
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
        // maintain sum of the close value of bars seen so far
        sum += data[i].close;
        if (i > window) {
            // throw out the bar at front of window's close value from sum and average
            sum -= data[i - window].close;
            data[i].sma = sum / window;
        }
        else 
        {
            // if at less than window, keep the average of bars seen so far
            data[i].sma = sum / (i + 1);
        }
    }
}

void DataFrame::CalculateRollingVolatility(int window) {
    double sum = 0;
    double mean = 0;
    double sum_squares = 0;
    
    for (std::vector<DataBar>::size_type i = 0; i != data.size(); i++) {
        // maintain sum of close values seen so far
        sum += data[i].close;
        if (i > window) {
            // drop the first value in the window as it slides along
            sum -= data[i - window].close;
            mean = sum / window;
            for (std::vector<DataBar>::size_type j = i - window; j != i; j++) {
                // sum of squares of the deviation from the mean
                sum_squares += std::pow(data[j].close - mean, 2);
            }
            data[i].volatility = std::pow(sum_squares / window, 0.5);
            sum_squares = 0;
        }
        else {
            // if we're at less than window size, operate on all values seen so far
            mean = sum / (i + 1);
            for (std::vector<DataBar>::size_type j = 0; j != i; j++) {
                sum_squares += std::pow(data[j].close - mean, 2);
            }
            data[i].volatility = std::pow(sum_squares / (i + 1), 0.5);
            sum_squares = 0;            
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

void DataFrame::CalculateRollingExtremes(int window) {
    // maintain highest high and lowest low
    double high = 0;
    double low = INFINITY;
    for (std::vector<DataBar>::size_type i = 0; i != data.size(); i++) {
        if (i < window) { 
            if (data[i].close > high) {
                high = data[i].close;
            }
            if (data[i].close < low) {
                low = data[i].close;
            }
        }
        else {
            // reset extremes for every bar's window
            high = 0;
            low = INFINITY;
            for (std::vector<DataBar>::size_type j = i - window; j != i; j++) {
                if (data[j].close > high) {
                    high = data[j].close;
                }
                if (data[j].close < low) {
                    low = data[j].close;
                }
            }   
        } 
        data[i].rolling_high = high;
        data[i].rolling_low = low; 
    }

}
