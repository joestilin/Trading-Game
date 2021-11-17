#ifndef DATAPARSER_H
#define DATAPARSER_H

#include "databar.h"
#include <vector>

class DataParser {
    public:
        DataParser();
        // parse data from file in same directory as executable and load into data vector
        void ParseData(std::vector<DataBar> &data);   
};

const std::string kDataFileName = "data.csv";   // defult name of the data file to be parsed

#endif