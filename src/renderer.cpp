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

    // initialize display constants
    InitializeDisplay();
    

 }

 void Renderer::Render(DataFrame const &dataframe, TradeLog const &tradelog, size_t const &current_bar) {

    
     UpdateXOffset(current_bar);

     ClearScreen();

     UpdateYScale(dataframe);

     DisplayBalance(tradelog);

     
     // draw
     
     int bar_number = 0;
     int x = 0;
     int y = 0;

     SDL_Rect block;
     block.x = 0;
     block.y = 0;
     block.w = 0;
     block.h = 0;

     for (auto &bar : dataframe.data) {

         SetCandleStickColor(bar);
         if (bar_number == current_bar) {
             SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);
         }

        // candle body position and dimensions
         x = bar_width * bar_number + bar_gap + x_offset;
         y = 0.5 * screen_height + y_scale * (dataframe.data[current_bar].sma - std::max(bar.open, bar.close));
         

         if (x >= left_margin && y >= top_margin) {
            block.x = x;
            block.y = y;
            block.h = std::abs(bar.open - bar.close)*y_scale;
            block.w = bar_width - bar_gap;
         }

         // Draw the candle
        SDL_RenderFillRect(sdl_renderer, &block);
         
        // wick body position and dimensions
        x = bar_width * bar_number + bar_gap + bar_width / 2 - 1 + x_offset;
        y = 0.5 * screen_height + y_scale * (dataframe.data[current_bar].sma - std::max(bar.high, bar.low));

        if (x >= left_margin && y >= top_margin) {
            block.x = x;
            block.y = y;
            block.h = std::abs(bar.high - bar.low)*y_scale;
            block.w = 1;
        }

        // Draw the wick
        SDL_RenderFillRect(sdl_renderer, &block);
        
        bar_number++;   
     }

     // update screen
     SDL_RenderPresent(sdl_renderer);

 }

void Renderer::UpdateWindow_Title(int const &fps) {
    std::string title{"FPS " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());

}

Renderer::~Renderer() { 
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}



void Renderer::InitializeDisplay() {
    bar_width = (screen_width - left_margin - right_margin) / max_bars_displayed;
}

void Renderer::UpdateXOffset(size_t const &current_bar) {
    x_offset = screen_width - right_margin - current_bar * bar_width;
    
}

void Renderer::ClearScreen() {
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);
}

void Renderer::UpdateYScale(DataFrame const &dataframe) {
    y_scale = screen_height / dataframe.volatility;
}

void Renderer::SetCandleStickColor(DataBar const &bar) {
    // set candlestick color
         if (bar.close >= bar.open) {
             SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
         }
         else {
             SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
         }
}

void Renderer::DrawCandleBody(DataFrame const &dataframe) {

}

void Renderer::DrawCandleWick(DataFrame const &dataframe) {

}

void Renderer::DisplayBalance(TradeLog const &tradelog) {

}

    
