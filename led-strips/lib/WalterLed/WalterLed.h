
#include "WalterLedStrip.h"
#ifndef __Walter_Led__
    #define __Walter_Led__

    class WalterLed
    {
    private:
        /* data */
    public:
        WalterLed(int index, WalterLedStrip *strip);
        ~WalterLed();
        void setColor(int r, int g, int b);
        int index;
        WalterLedStrip *strip;
        void
    };

    WalterLed::WalterLed(int index)
    {
    }

    WalterLed::~WalterLed()
    {
    }


#endif