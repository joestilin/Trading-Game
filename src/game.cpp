#include "game.h"
#include "renderer.h"
#include "controller.h"
#include "lobby.h"
#include "chart.h"

Game::Game() { }

void Game::Run() {
    std::size_t kFramesPerSecond{60};
    std::size_t kMsPerFrame = 1000 / kFramesPerSecond;
    std::size_t kScreenWidth = 1280;
    std::size_t kScreenHeight = 640;

    Renderer renderer(kScreenWidth, kScreenHeight);
    Controller controller;
    
    Lobby lobby;
    lobby.Run(controller, renderer, currentSymbol, kMsPerFrame);
    bool state = lobby.getState();

    Chart chart;
    chart.setState(state);
    chart.Run(controller, renderer, currentSymbol, kMsPerFrame);
}