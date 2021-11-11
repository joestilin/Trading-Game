#!/bin/bash

# install dependencies for TradingGame

# install sld2
sudo apt-get install libsdl2-dev

# install sld2 true type font extension
yes | sudo apt-get install libsdl2-ttf-dev

# install yfinance python package
pip install yfinance