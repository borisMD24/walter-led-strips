#include "WalterLed.h"

WalterLed::WalterLed(int index, WalterLedStrip *strip){
    this->index = index;
    this->strip = strip;
}
WalterLed::~WalterLed(){
}

void WalterLed::setColor(int r, int g, int b){
    this->strip.setPixelColor(this->index, r, g, b);
}