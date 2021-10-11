#include "dataframe.h"
#include <iostream>

DataFrame::DataFrame() { }

void DataFrame::LoadData() {
    parser.ParseData(data);
    CalculateData();
}

void DataFrame::PrintData() {
    for (auto databar : data) {
        std::cout << databar.date << " " << databar.open << " " 
        << databar.high << " " << databar.low << " " << databar.close << "\n";
    }
}

// Function to calculate attributes of the data including indicators
void DataFrame::CalculateData() {
    n_bars = data.size();
    max_high = 0;
    min_low = 1000000; // some large number

     for (auto &bar : data) {
         if (bar.high > max_high) {
             max_high = bar.high;
         }

         if (bar.low  < min_low) {
             min_low = bar.low;
         }
     }

     std::cout << "calculated some stuff\n";
}
