#pragma once

#include <vector>
#include "Usings.h"


struct Bar {
    Time timeStamp;
    Price open, high, low, close;
    Volume volume;
};

using Bars = std::vector<Bar>;
