#include "Bar.h"
#include "Side.h"
#include "Strategy.h"
#include "Trade.h"
#include "Global.h"
#include "Portfolio.h"
#include "BuyAndSell.h"
#include "SignalGenerator.h"
#include "Calculators.h"
#include "TradeDuplicationPreventor.h"
#include "SelectBestParameters.h"
#include <iostream>
#include <deque>

#pragma once

class MovingAverage
{
public:
    
    MovingAverage(int windowSize)
    : windowSize_(windowSize)
    , portfolio_(100000.0, 0)
    , strategy_(Strategy::MovingAverage)
    { }

    void SetWindowSize(int windowSize) { windowSize_ = windowSize; }
    int GetWindowSize() const { return windowSize_; }
    Strategy GetStrategy() const { return strategy_;}
    Trades GetTrades() const { return trades_; }
    Trades GetHistory() const { return history_; }
    Portfolio GetPortfolio() const { return portfolio_; }


    void CreateTrade(const Bars& bars)
    {
        Bar currentBar = bars[count_];
        Bar nextBar = bars[count_+1];
        double movingAverage = calculators_.CalculateMovingAverage(bars, windowSize_, count_);
        Side signal = signalGenerator_.GenerateMASignal(currentBar.close, movingAverage);
        BuyAndSell buyAndSell_(portfolio_, nextBar, trades_.back(), signal);
        TradeDuplicationPreventor preventDupes(trades_.back().GetSide(), signal);

        if(Side::Buy == signal)
        {
            bool dup = preventDupes.isDuplicateTrade();
            if(!dup){
            portfolio_ = buyAndSell_.Buy();
            trades_.push_back(Trade(nextBar, portfolio_.GetShares(), nextBar.open, Strategy::MovingAverage, signal, nextBar.timeStamp));
            }
            history_.push_back(Trade(nextBar, portfolio_.GetShares(), nextBar.open, Strategy::MovingAverage, signal, nextBar.timeStamp));
        }

        else if(Side::Sell == signal)
        {
            bool dup = preventDupes.isDuplicateTrade();
            if(!dup){
            portfolio_ = buyAndSell_.Sell();
            trades_.push_back(Trade(nextBar, portfolio_.GetShares(), nextBar.open, Strategy::MovingAverage, signal, nextBar.timeStamp));
            }
            history_.push_back(Trade(nextBar, portfolio_.GetShares(), nextBar.open, Strategy::MovingAverage, signal, nextBar.timeStamp));
        }
    }

    void Main(const Bars& bars)
    {
        trades_.push_back(Trade(bars[0], portfolio_.GetShares(), bars[0].open, Strategy::MovingAverage, Side::None, bars[0].timeStamp));
        for(count_=0; count_<bars.size()-1 ;count_++)
        {
            CreateTrade(bars);
        }
    }

private:
    int windowSize_;
    size_t count_;
    Strategy strategy_;
    Trades trades_;
    Trades history_;
    Calculators calculators_;
    MovingAverageSignalGenerator signalGenerator_;
    Portfolio portfolio_;

};