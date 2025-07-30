#include "Usings.h"
#include "Bar.h"
#include "Strategy.h"
#include "Side.h"
#include <vector>
#pragma once

class Trade
{
    public:
        Trade() = default;

        Trade(const Bar& bar, Volume shares, Price price, Strategy strategy, Side side, Time timeStamp)
            : bar_(bar)
            , shares_(shares)
            , price_(price)
            , strategy_(strategy)
            , side_(side)
            , timeStamp_(timeStamp)
            { }


        Bar GetBar() const { return bar_; }
        Volume GetShares() const { return shares_; }
        Price GetPrice() const { return price_; }
        Strategy GetStrategy() const { return strategy_; }
        Side GetSide() const { return side_; }
        Time GetTimeStamp() const { return timeStamp_; }

        void SetBar(const Bar& bar) { bar_ = bar; }
        void SetShares(Volume shares) { shares_ = shares; }
        void SetPrice(Price price) { price_ = price; }
        void SetStrategy(Strategy strategy) { strategy_ = strategy; }
        void SetSide(Side side) { side_ = side; }
        void SetTimeStamp(Time timeStamp) { timeStamp_ = timeStamp; }

    private:
        Bar bar_;       // The bar associated with the trade
        Volume shares_; // Number of shares traded
        Price price_;   // Price at which the trade occurred
        Strategy strategy_; // Strategy that executed the trade
        Side side_;
        Time timeStamp_; // Timestamp of the trade
};

using Trades = std::vector<Trade>;


