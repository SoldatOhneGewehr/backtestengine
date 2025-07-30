#include "Portfolio.h"
#include "Bar.h"

#pragma once

class BuyAndSell 
{
    public:
    
        BuyAndSell(Portfolio portfolio, const Bar& bar, const Trade& trade, Side signal)
        : portfolio_(portfolio)
        , bar_(bar)
        , trade_(trade)
        ,signal_(signal)
        { }

    Portfolio Buy()
    {   

        Price cash = portfolio_.GetCash();
        Price buyPrice = bar_.open;
        Volume sharesToBuy = static_cast<Volume>(cash / buyPrice); // Calculate the number of shares to buy
        portfolio_.SetShares(sharesToBuy + portfolio_.GetShares()); // Update the portfolio_ with the new shares
        portfolio_.SetCash(cash - (sharesToBuy * buyPrice)); // Deduct the cash spent on shares
        return portfolio_;
    }

    Portfolio Sell()
    {
        Volume shares = portfolio_.GetShares();
        Price sellPrice = bar_.open;
        Price cash = portfolio_.GetCash() + (shares * sellPrice); // Calculate the cash after selling shares
        portfolio_.SetCash(cash); // Update the portfolio with the new cash
        portfolio_.SetShares(0); // Set shares to zero after selling
        return portfolio_;

    }

    private:
        Portfolio portfolio_; // Reference to the portfolio
        const Bar& bar_; // Reference to the bar data
        const Trade& trade_;
        Side signal_;


};