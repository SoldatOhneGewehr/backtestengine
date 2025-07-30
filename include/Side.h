#pragma once

enum class Side
{
    Buy,   // Represents a buy order
    Sell,  // Represents a sell order
    None   // Represents no specific side
};

std::ostream& operator<<(std::ostream& os, Side side) {
    switch (side) {
        case Side::Buy:  return os << "Buy";
        case Side::Sell: return os << "Sell";
        case Side::None: return os << "None";
        default:              return os << "NotInitialized";
    }

}