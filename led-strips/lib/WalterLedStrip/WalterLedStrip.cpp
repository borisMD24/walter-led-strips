#include "WalterLedStrip.h"

WalterLedStrip::WalterLedStrip(int size, int pin)
    :Adafruit_NeoPixel(size, pin, NEO_GRB + NEO_KHZ800){
    this->size = size;
}
WalterLedStrip::~WalterLedStrip(){
}

void WalterLedStrip::setPixel(uint32_t color, uint16_t index){
    this->setPixelColor(index, color);
}

void WalterLedStrip::begin(){
    for (int i = 0; i < this->size; i++)
    {
        this->leds[i] = WalterLed(i);
    }   
    
}


void WalterLedStrip::update(){
        for (int i = 0; i < this->size; i++)
    {
        this->leds[i].update();
    }
}