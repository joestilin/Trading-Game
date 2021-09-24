#include <vector>
#include "databar.h"
#include "dataparser.h"

class DataFrame {

    public:
        DataFrame();
        void LoadData();
        void PrintData();
        
        std::vector<DataBar> *data;
        
    private:
        DataParser parser;

};