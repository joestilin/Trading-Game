#include "renderer.h"
#include <iostream>
#include <cmath>

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height) 
    : screen_width(screen_width), screen_height(screen_height) {

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        std::cerr << "SDL could not initialize\n";
        std::cerr << "SDL error: " << SDL_GetError() << "\n";
    }

    // create SDL window
    sdl_window = SDL_CreateWindow("Trading Game", SDL_WINDOWPOS_CENTERED, 
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN);
                            
    if (nullptr == sdl_window) {
        std::cerr << "window could not be created\n";
        std::cerr << "SDL error: " << SDL_GetError() << "\n";
    }

    // create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created\n";
        std::cerr << "SDL error: " << SDL_GetError() << "\n";
    }

 }

 void Renderer::Render(DataFrame const &dataframe) {
     SDL_Rect block;
     block.h = 50;
     block.w = 50;
     block.x = 100;
     block.y = 300;

     // clear screen

     SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
     SDL_RenderClear(sdl_renderer);

     // draw
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0xFF, 0xFF);

     double bar_width = screen_width / dataframe.n_bars;
     double slope = screen_height / (dataframe.max_high - dataframe.min_low);
     int bar_number = 0;

     for (auto &bar : dataframe.data) {

         // set candlestick color
         if (bar.close >= bar.open) {
             SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
         }
         else {
             SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
         }

        // candle body position and dimensions
         block.x = bar_width * bar_number;
         block.y = screen_height - slope * ((bar.open + bar.close) / 2 - dataframe.min_low);
         block.h = std::abs(bar.open - bar.close)*slope;
         block.w = bar_width - 5;

         // Draw the candle
         SDL_RenderFillRect(sdl_renderer, &block);

        // wick body position and dimensions
        block.x = bar_width * bar_number + bar_width / 2 - 1;
        block.y = screen_height - slope * ((bar.low + bar.high) / 2 - dataframe.min_low);
        block.h = std::abs(bar.high - bar.low)*slope;
        block.w = 1;

        // Draw the wick
         SDL_RenderFillRect(sdl_renderer, &block);

        bar_number++;   
     }

     // update screen
     SDL_RenderPresent(sdl_renderer);

 }

Renderer::~Renderer() { 
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

    
