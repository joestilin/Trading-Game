#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "dataframe.h"
#include "tradelog.h"
#include "symbol.h"
#include "state.h"

class Renderer {
    public:
        Renderer(const std::size_t screen_width, const std::size_t screen_height);
        ~Renderer();

        void RenderChart(DataFrame const &dataframe, TradeLog const &tradelog, 
                    size_t const &current_bar, Symbol const &currentSymbol);

        void RenderLobby(std::string const &inputText, TradeLog const &tradelog);

        void RenderEndGame(TradeLog const &tradelog, State const &state);

        void UpdateWindow_Title(int const &fps);

    private:

        // render std::string text with SDL_Color text_color center of text at int x, int y
        void RenderText(std::string text, SDL_Color text_color, int x, int y);
        void InitializeDisplay();
        void UpdateXOffset(size_t const &current_bar);
        void ClearScreen();
        void UpdateYScale(DataFrame const &dataframe, std::size_t const &current_bar);
        void MapX();
        void MapY();
        void SetCandleStickColor(DataBar const &bar, size_t const &current_bar, int bar_number);
        void DrawCandle(DataBar const &bar, int const &bar_number, 
                        size_t const &current_bar, DataFrame const &dataframe);
        void DrawCandleWick(DataFrame const &dataframe);
        void DrawOpenTradeLine(DataFrame const &dataframe, TradeLog const &tradelog, size_t const &current_bar);
        void DrawLine(double x1, double x2, double y1, double y2, int thickness);
        void DisplayBalance(TradeLog const &tradelog);
        void DisplayProgressBar(TradeLog const &tradelog);
        void DisplayOpenTradeBalance(TradeLog const &tradelog);
        void DisplaySymbol(Symbol const &currentSymbol);
        void DisplayInstructions();

    
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
        SDL_Texture *text_texture;
        TTF_Font *font = NULL;

        const std::size_t screen_width;
        const std::size_t screen_height;

        // Chart display variables
        
        int x_offset;               // pixels
        int y_offset{0};            // pixels
        int max_bars_displayed{100};
        int top_margin{10};
        int bottom_margin{10};
        int right_margin{10};
        int left_margin{10};
        int bar_width;
        int wick_width{1};
        int bar_gap{5};
        double x_scale;             // pixels per data unit
        double y_scale;

        // Colors
        

};
#endif