#pragma once

#include "Strategy.h"
#include "Trade.h"
#include "Portfolio.h"
#include "Bar.h"
#include "BuyAndSell.h"
#include "Side.h"

class Hodl {
private:
    Strategy strategy_;
    Trades trades_;
    Trades history_;
    Portfolio portfolio_;
    size_t count_ = 0;


public:
    Hodl()
        : portfolio_(100000.0, 0)
        , strategy_(Strategy::Hodl)
    { }

    Portfolio GetPortfolio() const { return portfolio_; }
    Trades GetTrades() const { return trades_; }
    Trades GetHistory() const { return history_; }
    Strategy GetStrategy() const { return strategy_; }
    Side GetSide() const { return Side::Buy; } // Hodl strategy does not involve buying or selling

    void CreateTrade(const Bars& bars)
    {
        auto currentBar = bars[count_];
        BuyAndSell buyAndSell_(portfolio_, currentBar, trades_.back(), Side::Buy);
        portfolio_ = buyAndSell_.Buy();
        trades_.push_back(Trade(currentBar, portfolio_.GetShares(), currentBar.open, strategy_, Side::Buy, currentBar.timeStamp));
    }

    void Main(const Bars& bars)
    {
        if (bars.empty()) return; // Ensure there are bars to process

        trades_.push_back(Trade(bars[0], portfolio_.GetShares(), bars[0].open, strategy_, Side::None, bars[0].timeStamp));
        for (count_ = 1; count_ < bars.size(); ++count_) {
            CreateTrade(bars);
        }
    }
};
