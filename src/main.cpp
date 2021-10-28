#include <iostream>
#include "renderer.h"
#include "controller.h"
#include "game.h"

// quantlib.org


int main () {
    std::cout << "Welcome the Trading Game. \nGood Luck!" << std::endl;


    // For now, input data is hardcoded; will be changed in the future
    // call python script to grab finanical data
    std::string data_reader_file = "/home/workspace/cpp-capstone/TradingGame/src/data.py";
    std::string arg1 = " DAL";
    std::string arg2 = " 1h";
    std::string command = "python3 ";
    command += data_reader_file + arg1 + arg2;
    system(command.c_str());

    std::size_t kFramesPerSecond{60};
    std::size_t kMsPerFrame = 1000 / kFramesPerSecond;
    std::size_t kScreenWidth = 1280;
    std::size_t kScreenHeight = 640;

    Renderer renderer(kScreenWidth, kScreenHeight);
    Controller controller;
    Game game;

    game.Run(controller, renderer, kMsPerFrame);

    
    return 0;
}