#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include "dataframe.h"
#include "tradelog.h"

class Renderer {
    public:
        Renderer(const std::size_t screen_width, const std::size_t screen_height);
        ~Renderer();

        void Render(DataFrame const &dataframe, TradeLog const &tradelog, 
                    bool const &scrolling);

        int bars_displayed;


    private:

        void InitializeDisplay();
        void UpdateScrolling(bool const &scrolling);
        void ClearScreen();
        void UpdateXScale(DataFrame const &dataframe);
        void UpdateYScale(DataFrame const &dataframe);
        void SetCandleStickColor(DataBar const &bar);
        void UpdateBarsDisplayed(DataFrame const &dataframe);
        void DrawCandleBody(DataFrame const &dataframe);
        void DrawCandleWick(DataFrame const &dataframe);
        void DisplayBalance(TradeLog const &tradelog);

        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        const std::size_t screen_width;
        const std::size_t screen_height;

        // Chart display variables
        int scroll_speed{50};       // pixels / frame
        int x_offset{1200};          // pixels
        int y_offset{0};            // pixels
        int max_bars_displayed{100};
        int top_margin{10};
        int bottom_margin{10};
        int right_margin{10};
        int left_margin{10};
        int bar_width;
        int bar_gap{5};
        double x_scale;             // pixels per data unit
        double y_scale;

};
#endif