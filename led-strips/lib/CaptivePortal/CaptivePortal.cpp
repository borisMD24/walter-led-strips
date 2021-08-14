#include "CaptivePortal.h"
#include <ESPAsyncWebServer.h>

using namespace std;
void CaptivePortal::setup(){
    wifi.mode(WIFI_AP);
    wifi.softAP("New Walter's");
    wifi.softAPConfig(IPAddress(8,8,4,4), IPAddress(8,8,4,4), IPAddress(255, 255, 255, 0));

    // if DNSServer is started with "*" for domain name, it will reply with
    // provided IP to all DNS request
    dnsServer.start(53, "*", wifi.softAPIP());
    loop();
        }
    void CaptivePortal::loop() 
    {
    bool looping = true;
    while (looping)
    {
  dnsServer.processNextRequest();
  WiFiClient client = WiFiserver.available();   // listen for incoming clients

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(SPIFFS.open("/index.html"));
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
    }

}

CaptivePortal::CaptivePortal()
{
  AsyncWebServer server(80);
}