#include "Usings.h"
#include "Trade.h"
#include "Calculators.h"
#include "SignalGenerator.h"
#include "Portfolio.h"
#include "BuyAndSell.h"
#include "Strategy.h"
#include "TradeDuplicationPreventor.h"

class DoubleMovingAverage
{
    public:

    DoubleMovingAverage() = default;

    DoubleMovingAverage(int shortWindowSize, int longWindowSize)
    : shortWindowSize_(shortWindowSize)
    , longWindowSize_(longWindowSize)
    , portfolio_(100000.0, 0)
    , strategy_(Strategy::DoubleMovingAverage)
    { }

    void SetShortWindowSize (int shortWindowSize) { shortWindowSize_ = shortWindowSize; }
    void SetLongWindowSize (int longWindowSize) { longWindowSize_ = longWindowSize; }
    Trades GetTrades() const { return trades_; }
    Trades GetHistory() const { return history_; }
    Portfolio GetPortfolio() const {return portfolio_; }
    Strategy GetStrategy() const { return strategy_; }

    void CreateTrade(const Bars& bars)
    {
        Bar currentBar = bars[count_];
        Bar nextBar = bars[count_+1]; 
        double shortAverage = calculators_.CalculateMovingAverage(bars, shortWindowSize_, count_);
        double longAverage = calculators_.CalculateMovingAverage(bars, longWindowSize_, count_);
        Side signal = signalGenerator_.GenerateMASignal(shortAverage, longAverage);
        BuyAndSell buyAndSell_(portfolio_, nextBar, trades_.back(), signal);
        TradeDuplicationPreventor preventDupes(trades_.back().GetSide(), signal);


        if(Side::Buy == signal)
        {
            bool dup = preventDupes.isDuplicateTrade();
            if(!dup){
                portfolio_ = buyAndSell_.Buy();
                trades_.push_back(Trade(nextBar, portfolio_.GetShares(), nextBar.open, Strategy::DoubleMovingAverage, signal, nextBar.timeStamp));
            }
            history_.push_back(Trade(nextBar, portfolio_.GetShares(), nextBar.open, Strategy::DoubleMovingAverage, signal, nextBar.timeStamp));
        }

        else if(Side::Sell == signal)
        {
            bool dup = preventDupes.isDuplicateTrade();
            if(!dup){
                portfolio_ = buyAndSell_.Sell();
                trades_.push_back(Trade(nextBar, portfolio_.GetShares(), nextBar.open, Strategy::DoubleMovingAverage, signal, nextBar.timeStamp));
            }
            history_.push_back(Trade(nextBar, portfolio_.GetShares(), nextBar.open, Strategy::DoubleMovingAverage, signal, nextBar.timeStamp));
        }

    }
 
    void Main(const Bars& bars)
    {
        trades_.push_back(Trade(bars[0], portfolio_.GetShares(), bars[0].open, Strategy::MovingAverage, Side::None, bars[0].timeStamp));

        for(count_=0; count_<bars.size()-1 ;count_++)
        {
            CreateTrade(bars);
            count_++;
        }
    }

    private:
        int shortWindowSize_;
        int longWindowSize_;
        size_t count_;
        Trades trades_;
        Trades history_;
        Calculators calculators_;
        MovingAverageSignalGenerator signalGenerator_;
        Portfolio portfolio_;
        Strategy strategy_;
};
