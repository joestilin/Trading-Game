#ifndef DATABAR_H
#define DATABAR_H

#include <string>


class DataBar {

    public:
        DataBar();

        std::string date;
        std::string time;
        float open;
        float high;
        float low;
        float close;
    
    private:
};

#endif