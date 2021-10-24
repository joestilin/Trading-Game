#ifndef TRADE_H
#define TRADE_H


enum Direction {FLAT, LONG, SHORT};

class Trade {
public:
    Trade();

    double entry_price;
    double exit_price;
    double amount;
    Direction direction;

};

#endif