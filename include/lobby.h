#ifndef LOBBY_H
#define LOBBY_H

#include "controller.h"
#include "renderer.h"
#include <fstream>
#include <sstream>
#include <algorithm>

class Lobby {
    public:

    Lobby();
    void ParseSymbols();
    void Run(Controller &controller, Renderer &renderer, std::size_t &target_frame_duration);
    void Update();
    bool getState();

    private:
    bool running = true;
    bool selection = false;
    bool validSelection = false;
    std::string inputText = " ";
    std::vector<std::string> symbols;
};

const std::string kSymbolFileName = "data/symbols.csv";



#endif