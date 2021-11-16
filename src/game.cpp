#include "game.h"

Game::Game() { }

void Game::Run() {
    std::size_t kFramesPerSecond{30};
    std::size_t kMsPerFrame = 1000 / kFramesPerSecond;
    std::size_t kScreenWidth = 1280;
    std::size_t kScreenHeight = 640;

    Renderer renderer(kScreenWidth, kScreenHeight);
    Controller controller;

    state = RUNNING;
    
    // cycle through new lobby and chart gameplay until player, wins, loses, or quits
    while (state == RUNNING) {
        Lobby lobby;
        lobby.Run(state, controller, renderer, tradelog, currentSymbol, kMsPerFrame);

        Chart chart;
        chart.Run(state, controller, renderer, tradelog, currentSymbol, kMsPerFrame);
    }

    // if player hasn't quit, display winning page, or display losing page
    if (state != QUIT) {
        EndGame endgame;
        endgame.Run(state, controller, renderer, tradelog, kMsPerFrame);
    }
    
    
}