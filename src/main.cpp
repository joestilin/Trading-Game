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

    std::size_t kFramesPerSecond{30};
    std::size_t kMsPerFrame = 1000 / kFramesPerSecond;
    std::size_t kScreenWidth = 1280;
    std::size_t kScreenHeight = 640;

    Renderer renderer(kScreenWidth, kScreenHeight);
    Controller controller;
    
    Lobby lobby;
    lobby.Run(controller, renderer, kMsPerFrame);
    bool state = lobby.getState();

    Game game;
    game.setState(state);
    game.Run(controller, renderer, kMsPerFrame);

    std::cout << "Game Over!" << "\n";
    
    return 0;
}
