#include "dataframe.h"
#include <iostream>

DataFrame::DataFrame() { }

void DataFrame::LoadData() {
    parser.ParseData(data);
}

void DataFrame::PrintData() {
    for (auto databar : data) {
        std::cout << databar.date << " " << databar.open << " " 
        << databar.high << " " << databar.low << " " << databar.close << "\n";
    }
}
