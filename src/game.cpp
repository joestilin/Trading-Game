#include "game.h"
#include "renderer.h"
#include "controller.h"
#include "lobby.h"
#include "chart.h"

Game::Game() { }

void Game::Run() {
    std::size_t kFramesPerSecond{30};
    std::size_t kMsPerFrame = 1000 / kFramesPerSecond;
    std::size_t kScreenWidth = 1280;
    std::size_t kScreenHeight = 640;

    Renderer renderer(kScreenWidth, kScreenHeight);
    Controller controller;

    running = true;
    
    while (running) {
        Lobby lobby;
        lobby.Run(running, controller, renderer, currentSymbol, kMsPerFrame);

        Chart chart;
        chart.Run(running, controller, renderer, currentSymbol, kMsPerFrame);
    }
    
}