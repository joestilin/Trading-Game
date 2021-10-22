#include "dataframe.h"
#include <iostream>

DataFrame::DataFrame() { }

void DataFrame::LoadData() {
    parser.ParseData(data);
    n_bars = data.size();
    CalculateExtremes();
    CalculateRollingMax(10);
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
