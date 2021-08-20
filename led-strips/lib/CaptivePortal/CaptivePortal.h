#include <DNSServer.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <SPIFFS.h>
#include <FS.h>
#include <Adafruit_NeoPixel.h>
#include <ESPAsyncWebServer.h>
#include <esp_event.h>
#include <esp_event_legacy.h>

using namespace std;
#ifndef CAPTIVE_PORTAL_H_INCLUDED
    #define CAPTIVE_PORTAL_H_INCLUDED

class CaptivePortal
{

    private:
        /* data */
        DNSServer dnsServer;
        WiFiClass wifi;
        WiFiServer wifiServer;
        void cb();

    public:
        void setup();
        void update();
        CaptivePortal();
};
#endif

