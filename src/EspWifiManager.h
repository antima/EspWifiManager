#ifndef ESPWIFIMANAGER_H_
#define ESPWIFIMANAGER_H_

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

#define AP_SSID "ESPWiFi-"

#define MAX_ATTEMPTS    5
#define WEB_SERVER_PORT 80
#define APRAND_LOWER    100
#define APRAND_UPPER    500


#ifndef DEBUG_MSG
#ifdef DEBUG_ESP_PORT
#define DEBUG_MSG(...) DEBUG_ESP_PORT.printf(__VA_ARGS__)
#else
#define DEBUG_MSG(...)
#endif
#endif


extern const char login_html[2660];


class ESPWifiManager {
    private:
        bool apMode;
        WiFiClient wifiClient;
        AsyncWebServer apServer;
        
        bool connectToWifi();
        void activateAPMode();

    public:
        ESPWifiManager();
        void loop();
        bool isConnected();
};

extern ESPWifiManager WiFiManager;

#endif