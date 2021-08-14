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
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <FS.h>
#include <Adafruit_NeoPixel.h>
using namespace std;
#ifndef CAPTIVE_PORTAL_H_INCLUDED
    #define CAPTIVE_PORTAL_H_INCLUDED

class CaptivePortal
{

    private:
        /* data */
        DNSServer dnsServer;
        WiFiClass wifi;
        WiFiServer WiFiserver;
        AsyncWebServer server;

        void setup();
        void loop();
    public:
        CaptivePortal();
};
#endif

