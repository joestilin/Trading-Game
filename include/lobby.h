#ifndef LOBBY_H
#define LOBBY_H

#include "controller.h"
#include "renderer.h"
#include "symbol.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include "symbol.h"

class Lobby {
    public:

    Lobby();
    void ParseSymbols();
    void Run(bool &running, Controller &controller, Renderer &renderer, Symbol &currentSymbol, std::size_t &target_frame_duration);
    void Update(Symbol &currentSymbol);

    private:
    bool selection = false;
    bool validSelection = false;
    std::string inputText = "";
    // std::vector<std::string> symbols;
    std::map<std::string, Symbol> symbols;
};

const std::string kSymbolFileName = "data/symbols.csv";

#endif