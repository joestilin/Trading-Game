#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

class Renderer {
    public:
        Renderer(const std::size_t screen_width, const std::size_t screen_height);
        ~Renderer();

        void Render();


    private:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

};
#endif