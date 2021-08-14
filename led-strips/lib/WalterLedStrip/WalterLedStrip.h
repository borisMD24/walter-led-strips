#include "WalterLed.h"
#include "Adafruit_NeoPixel.h"
#ifndef __Walter_Led_Strip_
    #define __Walter_Led_Strip__

    class WalterLedStrip : public Adafruit_NeoPixel
    {
    private:
        /* data */
    public:
        WalterLedStrip(int size);
        ~WalterLedStrip();
        void begin();
        int size;
        WalterLed leds[];
        void update();

    };

    WalterLedStrip::WalterLedStrip(int size)
    {
    }

    WalterLedStrip::~WalterLedStrip()
    {
    }


#endif