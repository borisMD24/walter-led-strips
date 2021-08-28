
#include "WalterLedStrip.h"
#ifndef __Walter_Led__
    #define __Walter_Led__

    class WalterLed
    {
    private:
        /* data */
    public:
        WalterLed(int index);
        ~WalterLed();
        void setColor(int r, int g, int b);
        int index;
        void
    };

    WalterLed::WalterLed(int index)
    {
    }

    WalterLed::~WalterLed()
    {
    }


#endif