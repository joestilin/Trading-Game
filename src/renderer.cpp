#include "renderer.h"
#include <iostream>

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height) {

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

 void Renderer::Render() {
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
     SDL_RenderFillRect(sdl_renderer, &block);

     // update screen
     SDL_RenderPresent(sdl_renderer);


 }

Renderer::~Renderer() { 
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}
    
