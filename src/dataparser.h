#ifndef DATAPARSER_H
#define DATAPARSER_H

#include "databar.h"
#include <vector>

class DataParser {
    public:
        DataParser();
        void ParseData(std::vector<DataBar> &data);   
};

const std::string kDataFileName = "/home/workspace/cpp-capstone/TradingGame/data/Data.csv";

#endif