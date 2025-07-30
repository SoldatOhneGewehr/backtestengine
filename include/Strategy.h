#include <string>
#include <string_view>
#pragma once

enum class Strategy {
    MovingAverage,
    Momentum,
    MeanReversion,
    Breakout,
    Arbitrage,
    Scalping,
    TrendFollowing,
    Hodl,
    DoubleMovingAverage
};

std::string_view to_string(Strategy strategy) 
{
    switch (strategy) {
        case Strategy::MovingAverage: return "Moving Average";
        case Strategy::DoubleMovingAverage: return "Double Moving Averages";
        case Strategy::Hodl: return "Hodl";

        default: return "Undefined";
    }
}