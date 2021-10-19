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
        void ClearScreen();
        void UpdateXScale(DataFrame const &dataframe);
        void SetCandleStickColor(DataBar const &bar);
        void UpdateBarsDisplayed(DataFrame const &dataframe);

        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        const std::size_t screen_width;
        const std::size_t screen_height;

        // Chart display variables
        int scroll_speed{10};       // pixels / frame
        int x_offset{1200};          // pixels
        int y_offset{0};            // pixels
        int bars_displayed;
        int max_bars_displayed{50};
        int top_margin{10};
        int bottom_margin{10};
        int right_margin{10};
        int left_margin{10};
        double bar_width;
        int bar_gap{5};
        double x_scale;             // pixels per data unit
        double y_scale;

};
#endif