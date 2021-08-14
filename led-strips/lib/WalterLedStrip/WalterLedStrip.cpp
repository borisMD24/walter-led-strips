#include "WalterLedStrip.h"

WalterLedStrip::WalterLedStrip(int size){
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