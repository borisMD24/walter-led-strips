#include "WalterLed.h"
#include "Adafruit_NeoPixel.h"
#ifndef __Walter_Led_Strip_
    #define __Walter_Led_Strip__

    class WalterLedStrip : Adafruit_NeoPixel
    {
    private:
        /* data */
    public:
        WalterLedStrip(int size, int pin);
        ~WalterLedStrip();
        void begin();
        int size;
        WalterLed leds[];
        void update();
        void setPixel(uint16_t);

    };

#endif