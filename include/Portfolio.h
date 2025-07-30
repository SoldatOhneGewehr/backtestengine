#include <unordered_map>
#include <string>
#include "Global.h"
#pragma once

class Portfolio
{
public:

    Portfolio() = default; 

    Portfolio(Volume cash, Volume shares)
    : cash_(cash)
    , shares_(shares)
    { }

    void SetCash(float cash){ cash_ = cash; }
    float GetCash() const { return cash_; }
    void SetShares(Volume shares) { shares_ = shares; }
    Volume GetShares() const { return shares_; }

private:

    float cash_;
    Volume shares_;
};

