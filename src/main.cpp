#include <iostream>

// quantlib.org


int main () {
    std::cout << "Welcome the Trading Game. \nGood Luck!" << std::endl;


    // For now, input data is hardcoded; will be changed in the future

    // call python script to grab finanical data
    std::string data_reader_file = "/home/workspace/cpp-capstone/TradingGame/src/data.py";
    std::string arg1 = " SPXL";
    std::string arg2 = " 1h";
    std::string command = "python3 ";
    command += data_reader_file + arg1 + arg2;
    system(command.c_str());

    
    return 0;
}