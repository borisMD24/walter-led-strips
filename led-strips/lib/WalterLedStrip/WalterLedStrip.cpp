#include "WalterLedStrip.h"

WalterLedStrip::WalterLedStrip(int size, int pin):Adafruit_NeoPixel::Adafruit_NeoPixel(size, pin,  NEO_GRB + NEO_KHZ800){
    this->size = size;
}
WalterLedStrip::~WalterLedStrip(){
}

void WalterLedStrip::begin(){
    for (int i = 0; i < this->size; i++)
    {
        this->leds[i] = WalterLed(i, &this);
    }
    
}

void WalterLedStrip::update(){
        for (int i = 0; i < this->size; i++)
    {
        this->leds[i].update();
    }
}