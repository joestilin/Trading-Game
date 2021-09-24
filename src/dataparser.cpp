#include "dataparser.h"
#include "databar.h"
#include <iostream>
#include <fstream>
#include <sstream>

DataParser::DataParser() { }

void DataParser::ParseData(std::vector<DataBar> &data) {

    std::string line;
    std::ifstream stream(kDataFileName);
    std::string date;
    std::string time;
    double open;
    double high;
    double low;
    double close;

    if (stream.is_open()) {
        std::cout << "File opened!" << "\n";
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            DataBar databar;
            linestream >> date >> time;
            databar.date = date;
            databar.time = time;
            data.push_back(databar);
        }

        stream.close();
    } else {
        std::cout << "Could not open data file" << "\n";
    }
    
}
