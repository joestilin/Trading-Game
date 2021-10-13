#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "dataframe.h"

class Renderer {
    public:
        Renderer(const std::size_t screen_width, const std::size_t screen_height);
        ~Renderer();

        void Render(DataFrame const &dataframe, bool const &scrolling);


    private:

        void InitializeDisplay();
        void UpdateScrolling(bool const &scrolling);

        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        const std::size_t screen_width;
        const std::size_t screen_height;

        // Chart display variables
        int scroll_speed{20};       // pixels / frame
        int x_offset{500};          // pixels
        int y_offset{0};            // pixels
        double x_scale;             // pixels per data unit
        double y_scale;

};
#endif