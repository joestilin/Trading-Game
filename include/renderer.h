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

        // Render the chart with data from dataframe, tradelog, current_bar, and currentSymbol
        void RenderChart(DataFrame const &dataframe, TradeLog const &tradelog, 
                    size_t const &current_bar, Symbol const &currentSymbol);

        // Render the lobby with inputText and tradelog
        void RenderLobby(std::string const &inputText, TradeLog const &tradelog);

        // Render the ending page with data from tradelog and state
        void RenderEndGame(TradeLog const &tradelog, State const &state);

        // Update the sdl window title with the current frames per second value.
        void UpdateWindow_Title(int const &fps);

    private:

        // render std::string text with SDL_Color text_color center of text at int x, int y
        void RenderText(std::string text, SDL_Color text_color, int x, int y);
        // set chart display values
        void InitializeDisplay();
        // change member x_offset depending on current_bar
        void UpdateXOffset(size_t const &current_bar);
        // clear the screen
        void ClearScreen();
        // Change y scale of chart depending on current_bar and dataframe
        void UpdateYScale(DataFrame const &dataframe, std::size_t const &current_bar);
        // Call prior to DrawCandle(). Sets the color of the candlestick depending on direction of price movement in the current bar.
        void SetCandleStickColor(DataBar const &bar, size_t const &current_bar, int bar_number);
        // Draw a candlestick representing bar at position dependent on bar_number, a current_bar, and dataframe
        void DrawCandle(DataBar const &bar, int const &bar_number, 
                        size_t const &current_bar, DataFrame const &dataframe);
        // Draw a line from the beginning of the open trade to current_bar's closing value.
        void DrawOpenTradeLine(DataFrame const &dataframe, TradeLog const &tradelog, size_t const &current_bar);
        // Draw a line from (x1, y1) to (x2, y2) with thickness thickness.
        void DrawLine(double x1, double x2, double y1, double y2, int thickness);
        // Display the the tradelog balance to the screen.
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

};
#endif