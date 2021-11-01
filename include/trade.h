#ifndef TRADE_H
#define TRADE_H


enum Direction {FLAT, LONG, SHORT};
enum Status {OPEN, CLOSED};

class Trade {
public:
    Trade();

    double entry_price;
    double exit_price;
    double amount;
    double shares{100};
    double profit;
    Status status;
    int index;
    Direction direction;

};

#endif