#include "Side.h"
#include "Usings.h"
#include "Bar.h"

#pragma once

class MovingAverageSignalGenerator
{


    public:

    MovingAverageSignalGenerator() = default; // Default constructor

    MovingAverageSignalGenerator
    (double firstParam, double secondParam)
        : firstParam_(firstParam)
        ,secondParam_(secondParam)
    { }

    Side GenerateMASignal(double firstParam_, double secondParam_) const
    {
        if (firstParam_ > secondParam_) {
            return Side::Buy; // Buy signal
        } else if (firstParam_ < secondParam_) {
            return Side::Sell; // Sell signal
        } else {
            return Side::None; // No action
        }
    }

    private:
        double firstParam_; // First parameter for the signal generation
        double secondParam_; // Second parameter for the signal generation

};