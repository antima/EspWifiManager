#ifndef ESPWIFIMANAGER_H_
#define ESPWIFIMANAGER_H_

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>


#define WEB_SERVER_PORT 80
#define APRAND_LOWER 100
#define APRAND_UPPER 500
#define RANDSSID_LEN 13

#ifndef DEBUG_MSG
#ifdef DEBUG_ESP_PORT
#define DEBUG_MSG(...) DEBUG_ESP_PORT.printf(__VA_ARGS__)
#else
#define DEBUG_MSG(...)
#endif
#endif


extern const char login_html[2660];

static void createAPServer(AsyncWebServer &server);
static bool validPostConnect(AsyncWebServerRequest *request);


class ESPWifiManager {
    private:
        bool apMode;
        WiFiClient wifiClient;
        AsyncWebServer apServer;
        
        bool connectToWifi();
        void activateAPMode();

    public:
        ESPWifiManager();
        bool isConnected();
};

extern ESPWifiManager ESPWifiManager;

#endif