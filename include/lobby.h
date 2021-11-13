#ifndef LOBBY_H
#define LOBBY_H

#include "controller.h"
#include "renderer.h"
#include "symbol.h"
#include "tradelog.h"
#include <iterator>
#include <time.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

class Lobby {
    public:

    Lobby();
    void ParseSymbols();
    void ParseSymbolFile(std::string filename);
    void Run(bool &running, Controller &controller, Renderer &renderer, TradeLog &tradelog, Symbol &currentSymbol, std::size_t &target_frame_duration);
    void Update(Symbol &currentSymbol);

    private:
    void RunPython(std::string symbol);
    bool selection = false;
    bool validSelection = false;
    bool random_selection = false;
    std::string inputText = "";
    std::map<std::string, Symbol> symbols;
};

const std::string kStockSymbolsFileName = "data/stocks.csv";
const std::string kETFSymbolsFileName = "data/etfs.csv";
const std::string kCryptoSymbolsFileName = "data/crypto.csv";
const std::string kCurrencySymbolsFileName = "data/currencies.csv";

#endif