# Trading Game

## Gamified stock, ETF, Crypto, and Forex trading

This game was developed for the capstone project for Udacity's C++ Nanodegree Program.

Players interact with historical price data pulled from Yahoo Finance. Players can create long and short trade positions in a fast paced scrolling game, with the goal of maximizing their profits.

## Dependencies for running locally

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

## Develelopment Notes / Approach

1. Vertical scale and offset of the chart during gameplay

On a first approach, the chart was scaled between the maximum and minimum close over the entire financial dataset. This resulted in a good display of data, but the player could intuit where the price was headed ahead of time (at worst least to the bottom of the screen, at best to the top). 

On the next iteration, it was realized that the a  vertical offset, rather than scaling provided a better experience. The player would ride along with the data, able to see just a portion of it, and experience the roller coaster effect as price moves up and down. As a start, the vertical offset was tied to an SMA (simple moving average) of bar closes, with a hard-coded SMA length (to be dynamically varied in a later update)

Now the window frame was moving along with up-and-down price action, but depending on the financial instrument or ticker, the vertical scale could appear too cramped or too spread out vertically. This was fixed by pre-calculating the volatility (same as standard deviation) of the entire financial dataset. It was found that simply dividing the screen height in pixels by the volatility provided a good vertical scaling.

