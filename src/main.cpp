#include <iostream>
#include "renderer.h"
#include "controller.h"
#include "lobby.h"
#include "game.h"

// quantlib.org

int main () {
    std::cout << "Welcome the Trading Game. \nGood Luck!" << std::endl;

    // For now, input data is hardcoded; will be changed in the future
    // call python script to grab finanical data
    //std::string data_reader_file = "/home/workspace/cpp-capstone/TradingGame/src/data.py";
    std::string data_reader_file = "python/data.py";
    std::string arg1 = " F";
    std::string arg2 = " 1h";
    std::string command = "python3 ";
    command += data_reader_file + arg1 + arg2;
    system(command.c_str());

    std::size_t kFramesPerSecond{30};
    std::size_t kMsPerFrame = 1000 / kFramesPerSecond;
    std::size_t kScreenWidth = 1280;
    std::size_t kScreenHeight = 640;

    Renderer renderer(kScreenWidth, kScreenHeight);
    Controller controller;
    Lobby lobby;
    Game game;
    
    lobby.Run(controller, renderer, kMsPerFrame);
    bool state = lobby.getState();
    game.setState(state);
    game.Run(controller, renderer, kMsPerFrame);

    std::cout << "Game Over!" << "\n";
    
    return 0;
}
