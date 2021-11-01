Gamified stock, ETF, Crypto, and Forex trading

Dependencies

sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-ttf-dev

Develelopment Notes / Approach

1. Vertical scale and offset of the chart during gameplay

On a first approach, the chart was scaled between the maximum and minimum close over the entire financial dataset. This resulted in a good display of data, but the player could intuit where the price was headed ahead of time (at worst least to the bottom of the screen, at best to the top). 

On the next iteration, it was realized that the a  vertical offset, rather than scaling provided a better experience. The player would ride along with the data, able to see just a portion of it, and experience the roller coaster effect as price moves up and down. As a start, the vertical offset was tied to an SMA (simple moving average) of bar closes, with a hard-coded SMA length (to be dynamically varied in a later update)

Now the window frame was moving along with up-and-down price action, but depending on the financial instrument or ticker, the vertical scale could appear too cramped or too spread out vertically. This was fixed by pre-calculating the volatility (same as standard deviation) of the entire financial dataset. It was found that simply dividing the screen height in pixels by the volatility provided a good vertical scaling.

