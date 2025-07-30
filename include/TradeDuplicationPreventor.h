#include "Trade.h"
#pragma once

class TradeDuplicationPreventor 
{
public:

    TradeDuplicationPreventor( Side prevTradeSide, Side currTradeSide)
    : prevTradeSide_(prevTradeSide)
    , currTradeSide_(currTradeSide)
    { }

    bool isDuplicateTrade()
    {
        if(prevTradeSide_ == currTradeSide_) { return true; }
        else { return false; }
    }


private:
    Side prevTradeSide_;
    Side currTradeSide_;
};