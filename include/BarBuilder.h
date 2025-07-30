#pragma once

#include "Usings.h"
#include "Bar.h"

class BarBuilder {
    public:
        BarBuilder( Time timeStamp, Price open, Price high, Price low, Price close, Volume volume)
        :timeStamp_{ timeStamp }
        , open_{ open }
        , high_{ high }
        , low_{ low }
        , close_{ close }
        , volume_{ volume }
        { }
    
        const Time& getTimeStamp() const {return timeStamp_;}
        const Price& getOpen() const {return open_;}
        const Price& getHigh() const {return high_;}
        const Price& getLow() const {return low_;}
        const Price& getClose() const {return close_;}
        const Volume& getVolume() const {return volume_;}

        Bar Build() const {
          return Bar{ timeStamp_, open_, high_, low_, close_, volume_ };
        }
    
    
    private:
        Time timeStamp_;
        Price open_, high_, low_, close_;
        Volume volume_;
    
    };