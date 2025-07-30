#include "Usings.h"
#include "Bar.h"
#include <cmath>

#pragma once

class Calculators
{
public:

    Calculators() = default;

    double CalculateMovingAverage (const Bars& bars, size_t windowSize, int count) const
    {
        if (count < windowSize) {
            return 0.0; // Not enough data to calculate the moving average
        }

        double sum = 0.0;
        for (int i = count - windowSize + 1; i < count + 1; ++i) {
            sum += bars[i].close; 
        }
        return sum / windowSize;
    }

    double CalculateStandartDeviation (const Bars& bars, size_t windowSize, int count) const
    {
        if (count < windowSize) {
            return 0.0; // Not enough data to calculate the standard deviation
        }

        double mean = CalculateMovingAverage(bars, windowSize, count);
        double sum = 0.0;

        for (int i = count - windowSize + 1; i < count + 1; ++i) {
            sum += std::pow(bars[i].close - mean, 2);
        }
        return std::sqrt(sum / windowSize);
    }
};

class PerformanceCalculators
{

    double CalculateDrawbackRatio(const Bars& bars) const
    {
        if (bars.empty()) {
            return 0.0;
        }

        double peak = bars[0].close;
        double maxDrawdown = 0.0;

        for (const auto& bar : bars) {
            if (bar.close > peak) {
                peak = bar.close;
            }
            double drawdown = (peak - bar.close) / peak;
            if (drawdown > maxDrawdown) {
                maxDrawdown = drawdown;
            }
        }
        return maxDrawdown;
    }
};