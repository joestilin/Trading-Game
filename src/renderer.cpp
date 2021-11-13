#include "renderer.h"
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

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

    // initialize TTF
    if (TTF_Init() < 0) {
        std::cout << "SDL_TTF could not be initialized: " << TTF_GetError << "\n";
    }

    font = TTF_OpenFont("fonts/Roboto-Bold.ttf", 18);
    if (font == NULL) {
        std::cout << "Font could not be loaded: " << TTF_GetError << std::endl;
    }

    // initialize display constants
    InitializeDisplay();
    
 }

 Renderer::~Renderer() { 
    SDL_DestroyWindow(sdl_window);
    TTF_CloseFont(font);
    //SDL_DestroyTexture(text_texture);
    SDL_Quit();
    TTF_Quit();
}

 void Renderer::RenderLobby(std::string const &inputText, TradeLog const &tradelog){
    ClearScreen();
    
    SDL_Color text_color = {200, 200, 200};
    
    std::stringstream balance_text;
    balance_text << "Your balance is $" << std::setprecision(2) << std::fixed << tradelog.balance;
    std::string goalText = "Try to get to $1MM";
    std::string queryText = "Type in a symbol and hit enter:";
    std::string exampleText = "Ideas: AAPL, TSLA, BTC-USD, or press right arrow for a random chart!";

    // render the balance text
    RenderText(balance_text.str(), text_color, screen_width / 2, screen_height / 5);
    // render the query text
    RenderText(queryText, text_color, screen_width / 2, 2 * screen_height / 5);
    // render user input text
    RenderText(inputText, text_color, screen_width / 2, 3 * screen_height / 5);
    // render the example text
    RenderText(exampleText, text_color, screen_width / 2, 4 * screen_height / 5 );
    

    // update screen
    SDL_RenderPresent(sdl_renderer);

 }
 
 void Renderer::RenderText(std::string text, SDL_Color text_color, int x, int y) {

     // only render text if the string contains characters
     if (text.length() > 0 ) {
        SDL_Rect box;
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
        text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text_surface);
        box.x = x - text_surface->w / 2;
        box.y = y - text_surface->h / 2;
        box.h = text_surface->h;
        box.w = text_surface->w;
        SDL_RenderCopy(sdl_renderer, text_texture, NULL, &box);
        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text_surface);
     }

 }

 void Renderer::RenderChart(DataFrame const &dataframe, TradeLog const &tradelog, 
                            size_t const &current_bar, Symbol const &currentSymbol) {

    
     UpdateXOffset(current_bar);

     ClearScreen();

     UpdateYScale(dataframe, current_bar);

     DisplayBalance(tradelog);

     DisplaySymbol(currentSymbol);
     
     int bar_number = 0;

     // draw the bars in the dataset
     for (auto &bar : dataframe.data) {

         SetCandleStickColor(bar, current_bar, bar_number);

         DrawCandle(bar, bar_number, current_bar, dataframe);
        
        bar_number++;
     }

    if (tradelog.trades.size() > 0 && tradelog.trades.back().status == Status::OPEN) {
        DrawOpenTradeLine(dataframe, tradelog, current_bar);
        DisplayOpenTradeBalance(tradelog);
    }

     // update screen
     SDL_RenderPresent(sdl_renderer);

 }

void Renderer::UpdateWindow_Title(int const &fps) {
    std::string title{"FPS " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());

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

void Renderer::UpdateYScale(DataFrame const &dataframe, std::size_t const &current_bar) {
    // y_scale = 0.1*screen_height / dataframe.data[current_bar].volatility;
    // y_scale = 5 * screen_height / dataframe.volatility;
    y_scale = screen_height / (dataframe.data[current_bar].rolling_high - dataframe.data[current_bar].rolling_low);
}

void Renderer::SetCandleStickColor(DataBar const &bar, size_t const &current_bar, int bar_number) {
    // set candlestick color
    if (bar.close >= bar.open) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
    }
    else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    if (bar_number == current_bar) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);
    }
}

void Renderer::DrawCandle(DataBar const &bar, int const &bar_number, 
                                size_t const &current_bar, DataFrame const &dataframe) {
    int x = 0;
    int y = 0;

    SDL_Rect block;
    block.x = 0;
    block.y = 0;
    block.w = 0;
    block.h = 0;

    // candle body position and dimensions
    x = bar_width * bar_number + bar_gap + x_offset;
    y = 0.5 * screen_height + y_scale * (dataframe.data[current_bar].large_sma - std::max(bar.open, bar.close));
         

    if (x >= left_margin && y >= top_margin) {
        block.x = x;
        block.y = y;
        block.h = std::abs(bar.open - bar.close)*y_scale;
        block.w = bar_width - bar_gap;
    }
    // Draw the candle
    SDL_RenderFillRect(sdl_renderer, &block);

    // wick body position and dimensions
        x = bar_width * bar_number + bar_gap + bar_width / 2 - wick_width + x_offset;
        y = 0.5 * screen_height + y_scale * (dataframe.data[current_bar].large_sma - std::max(bar.high, bar.low));

        if (x >= left_margin && y >= top_margin) {
            block.x = x;
            block.y = y;
            block.h = std::abs(bar.high - bar.low)*y_scale;
            block.w = wick_width;
        }

    // Draw the wick
    SDL_RenderFillRect(sdl_renderer, &block);
}

void Renderer::DrawOpenTradeLine(DataFrame const &dataframe, TradeLog const &tradelog, size_t const &current_bar) {
    // Draw open trade line
    // endpoints of the line
    double x1 = tradelog.trades.back().index * bar_width + bar_gap + x_offset;
    double y1 = 0.5 * screen_height + y_scale * (dataframe.data[current_bar].large_sma - tradelog.trades.back().entry_price);
    double x2 = current_bar * bar_width + bar_gap + x_offset;
    double y2 = 0.5 * screen_height + y_scale * (dataframe.data[current_bar].large_sma - dataframe.data[current_bar].close);
    
    switch (tradelog.current_position) {
        case LONG:
            if (y1 >= y2) {
                SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
            }
            else {
                SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
            }
            break;
        case SHORT:
            if (y1 <= y2) {
                SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
            }
            else {
                SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
            }
            break;

        
    }
    

    DrawLine(x1, y1, x2, y2, 10);
}

void Renderer::DisplayBalance(TradeLog const &tradelog) {
    std::string body_text = "Balance:";
    std::stringstream balance_text;
    balance_text << "$" << std::setprecision(2) << std::fixed << tradelog.balance;
    SDL_Color text_color = {200, 200, 200};
    RenderText(body_text, text_color, screen_width / 10, screen_height / 20);
    if (tradelog.balance >= 0 ) {
        text_color = {0x00, 0xFF, 0x00};
    }
    else {
        text_color = {0xFF, 0x00, 0x00};
    }
    RenderText(balance_text.str(), text_color, 2 * screen_width / 10, screen_height / 20);
}

void Renderer::DisplayOpenTradeBalance(TradeLog const &tradelog) {
    std::string body_text = "Trade Profit:";
    std::stringstream balance_text;
    balance_text << "$" << std::setprecision(2) << std::fixed << tradelog.trades.back().profit;
    SDL_Color text_color = {200, 200, 200};
    RenderText(body_text, text_color, 3 * screen_width / 10, screen_height / 20);
    if (tradelog.trades.back().profit >= 0 ) {
        text_color = {0x00, 0xFF, 0x00};
    }
    else {
        text_color = {0xFF, 0x00, 0x00};
    }
    RenderText(balance_text.str(), text_color, 4 * screen_width / 10, screen_height / 20);
}

void Renderer::DisplaySymbol(Symbol const &currentSymbol) {
    std::string symbol_text = currentSymbol.symbol;
    std::string name_text = currentSymbol.name;
    SDL_Color text_color = {200, 200, 200};
    RenderText(symbol_text, text_color, 5 * screen_width / 10, screen_height / 20);
    RenderText(name_text, text_color, 8 * screen_width / 10, screen_height / 20);
}

void Renderer::DrawLine(double x1, double y1, double x2, double y2, int thickness) {
    for (int i = 0; i < thickness; i++) {
        SDL_RenderDrawLine(sdl_renderer, x1, y1 + i, x2, y2 + i);
    }
}

    
