#include <deque>

#pragma once

using TradeDeque = std::deque<Trades>;
using ParameterDeque = std::deque<ParameterInstance>;

class SelectBestParameters
{

public:
    SelectBestParameters() = default;

    ParameterDeque GetBestParameters() const { return bestParameters_; }
    void ClearBestParameters() { bestParameters_.clear(); }

    void IsBestParams(ParameterInstance paramInstance_, Trades trades_, Portfolio portfolio_)
    {
        if (trades_.empty()) {
            return; // No trades to evaluate
        }

        Price currVal_ = 0;
        currVal_ = portfolio_.GetCash() + (trades_.back().GetShares() * trades_.back().GetPrice());
        if (currVal_ > bestVal_) {
            bestVal_ = currVal_;
            FIFO(paramInstance_, 5);
        }
    }

private:

    ParameterDeque bestParameters_;
    Price bestVal_ = 0;
    
    void FIFO(ParameterInstance paramInstance_, size_t maxSize) {

            if (bestParameters_.size() < maxSize) {
                bestParameters_.push_back(paramInstance_);
            } else {
                bestParameters_.pop_front();
                bestParameters_.push_back(paramInstance_);
            }
    }
};

class SelectBestTrades
{


public:
    SelectBestTrades() = default;

    TradeDeque GetBestTrades() const { return bestTrades_; }

    void IsBestTrade(Trades trades_, Portfolio portfolio_)
    {
        if (trades_.empty()) {
            return; // No trades to evaluate
        }

        Price currVal_ = portfolio_.GetCash() + (trades_.back().GetShares() * trades_.back().GetPrice());
        if (currVal_ > bestVal_) {
            bestVal_ = currVal_;
            FIFO(trades_, 5);
        }
    }

private:

    TradeDeque bestTrades_;
    Price bestVal_ = 0;

    void FIFO(const Trades trades_, size_t maxSize) {
        if (bestTrades_.size() < maxSize) {
            bestTrades_.push_back(trades_);
        } else {
            bestTrades_.pop_front();
            bestTrades_.push_back(trades_);
        }
    }
};
