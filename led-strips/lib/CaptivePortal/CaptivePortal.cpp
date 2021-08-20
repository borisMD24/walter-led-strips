#include "CaptivePortal.h"

using namespace std;
void CaptivePortal::setup(){

  Serial.begin(115200);
  const char* ssid = "uPesy_AP";
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  void (CaptivePortal::*f)();
  f = &CaptivePortal::cb;
  esp_err_t esp_event_loop_init(SYSTEM_EVENT_AP_START);
}
void CaptivePortal::cb(){
  const byte DNS_PORT = 53;
  IPAddress apIP(8,8,4,4); // The default android DNS
  delay(1000);
  this->dnsServer.start(DNS_PORT, "*", apIP);
  this->wifiServer = WiFiServer(80);
  this->wifiServer.begin();
}
void CaptivePortal::update() 
{
    this->dnsServer.processNextRequest();
    WiFiClient client = this->wifiServer.available();   // listen for incoming clients

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

  Serial.begin(115200);
  Serial.println("updated");
}

CaptivePortal::CaptivePortal()
{
  this->setup();
}