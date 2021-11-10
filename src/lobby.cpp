#include "lobby.h"
#include <iostream>

Lobby::Lobby() { 
    // load the file of financial symbols into a vector
    ParseSymbols();
}

void Lobby::Run(Controller &controller, Renderer &renderer, std::size_t &target_frame_duration) {

     // timing variables
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    // enable text input
    SDL_StartTextInput();

    while (running && !validSelection) {
        frame_start = SDL_GetTicks();

        controller.HandleLobbyInput(running, selection, inputText);
        
        Update();

        renderer.RenderLobby(inputText);
        
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

}

void Lobby::Update() {
    if (selection) {
        if (std::find(symbols.begin(), symbols.end(), inputText) != symbols.end()) {
            std::string data_reader_file = "python/data.py";
            std::string arg1 = " " + inputText;
            std::string arg2 = " 1h";
            std::string command = "python3 ";
            command += data_reader_file + arg1 + arg2;
            int error = system(command.c_str());
            std::cout << error << std::endl;
        }
        else {
            std::cout << "Invalid symbol" << std::endl;
            selection = false;
        }
    }
}

bool Lobby::getState() {
    return running;
}

void Lobby::ParseSymbols() {
    std::string line;
    std::ifstream stream(kSymbolFileName);

    std::vector<std::string> row;

    if (stream.is_open()) {
        std::cout << "File opened!" << "\n";


        while (std::getline(stream, line)) {
            row.clear();

            std::istringstream linestream(line);

            DataBar databar;

            while (linestream.good()) {
                std::string substr;
                std::getline(linestream, substr, ',');
                row.push_back(substr);
            }

            symbols.push_back(row[0]);
        }

        stream.close();
    } else {
        std::cout << "Could not open data file" << "\n";
    }

}

