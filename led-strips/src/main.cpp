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
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    14

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 84

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
 
AsyncWebServer server(80);
IPAddress apIP(8,8,4,4);

WiFiServer WiFiserver(80);
const char* ssid = "Freebox-5A276C";
const char* password = "cwh7fq3wcrq3vktmqkwc52";

const char* PARAM_MESSAGE = "message";
const char* r = "r";
const char* g = "g";
const char* b = "b";


void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}


DNSServer dnsServer;

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print("<!DOCTYPE html><html><head><title>Captive Portal</title></head><body>");
    response->print("<p>This is out captive portal front page.</p>");
    response->printf("<p>You were trying to reach: http://%s%s</p>", request->host().c_str(), request->url().c_str());
    response->printf("<p>Try opening <a href='http://%s'>this link</a> instead</p>", WiFi.softAPIP().toString().c_str());
    response->print("</body></html>");
    request->send(response);
  }
};


void setup() {
  strip.clear();
  strip.begin();
    Serial.begin(115200);
    /* spiffs */
    SPIFFS.begin();
    File root = SPIFFS.open("/");
    File file = root.openNextFile();

    while (file)
    {
      Serial.println("file");
      Serial.println(file.name());
      file.close();
      root.openNextFile();
    }
    

    /*wifi*/
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
          WiFi.mode(WIFI_AP);
          WiFi.softAP("New Walter's");
          WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

          // if DNSServer is started with "*" for domain name, it will reply with
          // provided IP to all DNS request
          dnsServer.start(53, "*", apIP);
          server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send(SPIFFS, "/portal.html", "text/html");

    });

          server.begin();
    } else {

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });

    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message);
    });
    server.on("/fill", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String red = request->getParam(r)->value();
        String green = request->getParam(g)->value();
        String blue = request->getParam(b)->value();
        if (request->hasParam("r")) {

            strip.fill(strip.Color((uint8_t)atoi(red.c_str()), (uint8_t)atoi(green.c_str()), (uint8_t)atoi(blue.c_str())), 0, LED_COUNT);
            strip.show();
            Serial.println(red);
            Serial.println(green);
            Serial.println(blue);

        }
        request->send(200, "text/plain", "Hello, GET: ");
    });
    server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.html", "text/html");
    });
    server.on(
    "/post",
    HTTP_POST,
    [](AsyncWebServerRequest * request){},
    NULL,
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
      String body;
      for (size_t i = 0; i < len; i++) {
        body += static_cast<char>(data[i]);
      }
 
      Serial.print(body);
      StaticJsonDocument<800> doc;
      DeserializationError error = deserializeJson(doc, body);
      const char* sensor = doc["test"];
      Serial.print(sensor);
      request->send(200);
  });
    server.onNotFound(notFound);

    server.begin();
    }
  
    strip.fill(strip.Color(0, 255, 0), 0, LED_COUNT);
    strip.show();
}

void loop() {
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