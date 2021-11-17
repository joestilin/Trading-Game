# Trading Game

## Gamified stock, ETF, Crypto, and Forex trading

This game was developed for the capstone project for Udacity's C++ Nanodegree Program.

Players interact with up to the minute price data pulled from Yahoo Finance. Players can create long and short trade positions in a fast paced scrolling game, with the goal of maximizing their profits.

Currently supported financial symbols include:

8,094 stock symbols listed on NASDAQ, NYSE, and AMEX

2,506 ETF symbols

11 Cryptocurrency symbols

13 major currency pairs

## Gameplay

Players begin with $100,000 with the goal of reaching $1MM. They can type in a financial symbol or press the right arrow key to choose a random symbol from the over 10,000 financial instruments supported. 

Controls:

Up arrow: BUY

Down arrow: SELL

If you buy first, you enter a long trade and your profit will be positive when price moves up. Down arrow to exit a long trade.

Alternatively, if you sell first, you enter a short trade and your profit will be positive when price moves lower. Up arrow to exit a short trade.

The game ends when the player wins by exceeding the goal ($1MM), or loses by falling below $0.

At any time the game can be exited by closing the game window.

## Dependencies for running locally

For linux users, dependencies can be installed in one command by running `./setup.bash` after cloning this repo.

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL_TTF
  * Run `sudo apt-get install libsdl2-ttf-dev`
* Yahoo Finance
  * Run `pip install yfinance`
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Build Instructions
1. Clone this repository
`git clone http://www.github.com/joestilin/Trading-Game`
2. Make a build directory in the top level directory:
`mkdir build && cd build`
3. Compile:
`cmake .. && make`
4. Run:
`./TradingGame`

## Rubric Points Addressed
List of rubric points addressed for the Udacity C++ Nanodegree capstone project:

1. "The project demonstrates an understanding of C++ functions and control structures."
  * "A variety of control structures are used in the project"
    * `while` loops in `Run()` member functions in `game.cpp` (17-23) `lobby.cpp` (27-54), `chart.cpp` (22-46) and `endgame.cpp` (20-46).
    * `for` loops in `CalculateSMA()` (26-39), `CalculateRollingVolatility` (47-70), and `CalculateRollingExtremes` (95-119) member functions in `dataframe.cpp`; and with use of `auto` keyword in a `for` loop in `RenderChart` function in `renderer.cpp` (121-128)
    * `switch` and `case` control blocks in functions `HandleControlInput` (8-22), `HandleLobbyInput` (29-67), and `HandleEndGameInput` (74-78) in `controller.cpp`. Also in `Update` function (78-87, 91-101), `OpenTrade` function (108-125), `CloseShortTrade` function (132-144), `CloseLongTrade` function (149-161), and `UpdateOpenTradeProfit` function (106-174) in `chart.cpp`.
  * "The project code is clearly organized into functions."
    * See header files for function prototypes and `.cpp` files for implementation. Functions perform small tasks and repeat code is avoided throughout the project using functions.

2. "The project reads data from a file and process the data, or the program writes data to a file."
  * "The project reads data from an external file or writes data to a file as part of the necessary operation of the program."
    * See `dataparser.cpp` wherein `ParseData` function reads data line by line from a .csv file of financial data, processes it in a `DataBar` object.
    * Also see `lobby.cpp` in which the `ParseSymbolFile` function (101-133) reads data from a .csv file of financial symbols and their names, and stores them a `<std::string, Symbol>`
    * The project also creates .csv files read by a `DataParser` by using `system` to run a Python script that pulls the latest financial data from Yahoo Finance.

3. "The project accepts user input and processes the input."


## Develelopment Notes / Approach

1. Vertical scale and offset of the chart during gameplay

On a first approach, the chart was scaled between the maximum and minimum close over the entire financial dataset. This resulted in a good display of data, but the player could intuit where the price was headed ahead of time (at worst least to the bottom of the screen, at best to the top). 

On the next iteration, it was realized that the a  vertical offset, rather than scaling provided a better experience. The player would ride along with the data, able to see just a portion of it, and experience the roller coaster effect as price moves up and down. As a start, the vertical offset was tied to an SMA (simple moving average) of bar closes, with a hard-coded SMA length (to be dynamically varied in a later update)

Now the window frame was moving along with up-and-down price action, but depending on the financial instrument or ticker, the vertical scale could appear too cramped or too spread out vertically. This was fixed by pre-calculating the volatility (same as standard deviation) of the entire financial dataset. It was found that simply dividing the screen height in pixels by the volatility provided a good vertical scaling.

