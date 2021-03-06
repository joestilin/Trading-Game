#include "lobby.h"
#include <iostream>

Lobby::Lobby() { 
    // load the file of financial symbols into the symbols map
    ParseSymbols();
    // initialize random number generator with seed from time
    time_t t;
    srand((unsigned) time(&t));
}

void Lobby::Run(State &state, Controller &controller, Renderer &renderer, 
                TradeLog &tradelog, Symbol &currentSymbol, std::size_t &target_frame_duration) {

     // timing variables
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    // enable text input
    SDL_StartTextInput();

    // loop until player types in a valid financial symbol or chooses a random selection
    while (state == RUNNING && !validSelection) {
        frame_start = SDL_GetTicks();

        controller.HandleLobbyInput(state, selection, random_selection, inputText);
        
        Update(currentSymbol);

        renderer.RenderLobby(inputText, tradelog);
        
        // timing
        frame_end = SDL_GetTicks();
        frame_count++;
        frame_duration = frame_end - frame_start;

        // calculate frames per second
        if (frame_end - title_timestamp > 1000) {
            renderer.UpdateWindow_Title(frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // throttle the loop to target frame rate
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
    // end text input
    SDL_StopTextInput();
}

void Lobby::Update(Symbol &currentSymbol) {
    // check if entered text is a supported symbol in symbols map
    if (selection) {
        if (symbols.find(inputText) != symbols.end()) {
            // valid symbol. pull data from yfinance and set the current symbol
            RunPython(inputText);
            validSelection = true;
            currentSymbol = symbols[inputText];
        }
        else {
            // invalid symbol
            std::cout << "Invalid symbol" << std::endl;
            selection = false;
            inputText = "";
        }
    }
    else if (random_selection) {
        // pick a random symbol from the map of symbols
        int random_index = rand() % symbols.size();
        std::map<std::string, Symbol>::iterator item = symbols.begin();
        std::advance(item, random_index);
        currentSymbol = item->second;
        validSelection = true;
    }
}

void Lobby::RunPython(std::string symbol){
    // use system to run python script that calls yfinance
    std::string data_reader_file = "python/data.py";
    std::string arg1 = " " + symbol;
    std::string arg2 = " 1h";
    std::string command = "python3 ";
    command += data_reader_file + arg1 + arg2;
    int error = system(command.c_str());
    std::cout << error << std::endl;
}

void Lobby::ParseSymbols() {
    // parse each csv file of financial symbols
    ParseSymbolFile(kStockSymbolsFileName);
    ParseSymbolFile(kETFSymbolsFileName);
    ParseSymbolFile(kCryptoSymbolsFileName);
    ParseSymbolFile(kCurrencySymbolsFileName);
}

void Lobby::ParseSymbolFile(std::string filename) {
    std::string line;
    std::ifstream stream(filename);

    std::vector<std::string> row;

    if (stream.is_open()) {
        // std::cout << "File opened!" << "\n";

        while (std::getline(stream, line)) {
            row.clear();

            std::istringstream linestream(line);

            Symbol symbol;

            while (linestream.good()) {
                std::string substr;
                std::getline(linestream, substr, ',');
                row.push_back(substr);
            }
            // add new symbol to the symbol map
            symbol.symbol = row[0];
            symbol.name = row[1];
            symbols[row[0]] = symbol;    
        }

        stream.close();
    } else {
        std::cout << "Could not open data file" << "\n";
    }

}

