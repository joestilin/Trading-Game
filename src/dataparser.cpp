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
    bool firstline = true;

    std::vector<std::string> row;

    if (stream.is_open()) {
        std::cout << "File opened!" << "\n";
        while (std::getline(stream, line)) {
            if (!firstline) {
                row.clear();

                std::istringstream linestream(line);

                DataBar databar;

                while (linestream.good()) {
                    std::string substr;
                    std::getline(linestream, substr, ',');
                    row.push_back(substr);
                }

                databar.date = row[0];
                databar.open = std::stod(row[1]);
                databar.high = std::stod(row[2]);
                databar.low = std::stod(row[3]);
                databar.close = std::stod(row[4]);
                data.push_back(databar);
            }
            firstline = false;
        }

        stream.close();
    } else {
        std::cout << "Could not open data file" << "\n";
    }
    
}
