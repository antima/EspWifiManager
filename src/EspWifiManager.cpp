#include <stdio.h>
#include "EspWifiManager.h"
#include "EepromManager/EepromManager.hpp"

/**
 * @brief 
 * 
 * @param request 
 * @return true 
 * @return false 
 */
bool validPostConnect(AsyncWebServerRequest *request) 
{
    // Validates a post request coming from the /connect endpoint, putting the received ssid and key
    // into values and returning true if the content of the request was valid.
    // If false is returned, nothing can be said about the contents of values;
    bool p1 = request->hasParam("ssid", true);
    bool p2 = request->hasParam("key", true);

    bool isInvalid = !p1 || !p2;
    
    if (isInvalid) {
        return false;
    }
    String ssid = request->getParam("ssid", true)->value();
    String key = request->getParam("key", true)->value();

    const unsigned int l1 = ssid.length();
    const unsigned int l2 = key.length();

    return l1 > 0 && l1 <= SSID_LENGTH && l2 > 0 && l2 <= KEY_LENGTH;
}


void createAPServer(AsyncWebServer &server)
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", login_html);
    });

    server.on("/connect", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (!validPostConnect(request))
        {
            request->send(422, "text/plain", "wrong syntax");
            return;
        }
        request->send(200, "text/plain", "ok");
        delay(1000);

        ConnectionInfo info;

        info.ok = true;
        String ssid = request->getParam("ssid", true)->value();
        String key = request->getParam("key", true)->value();

        strncpy(info.ssid, ssid.c_str(), SSID_LENGTH);
        strncpy(info.key, key.c_str(), KEY_LENGTH);

        EeManager.writeConnectionInfo(&info);
        ESP.reset();
    });
}

/*****************************************************
 *                   Public APIs
 ****************************************************/

/**
 * @brief Construct a new ESPWifiManager::ESPWifiManager object
 * 
 */
ESPWifiManager::ESPWifiManager() : apMode(false), wifiClient(), apServer(WEB_SERVER_PORT)
{
    createAPServer(apServer);
}


/**
 * @brief Connection check that has to be called in the 
 *        loop function, this switches to AP mode on connection error
 * 
 * @return true  The ESP is currently connected to the WiFi
 * @return false The ESP is in AP mode
 */
bool ESPWifiManager::isConnected() 
{
    bool wifiConn = WiFi.isConnected();
    if (!wifiConn) {
        bool okWifi = connectToWifi();
        if (!okWifi) {
            activateAPMode();
            return false;
        }
    }
    return true;
}


/*****************************************************
 *                Private methods
 ****************************************************/


bool ESPWifiManager::connectToWifi() 
{
    WiFi.mode(WIFI_STA);
    uint8_t attempt = 0;

    ConnectionInfo info = EeManager.readConnectionInfo();

    while (attempt < MAX_ATTEMPTS) {
        attempt++;
        DEBUG_MSG("Connecting to the WiFi - Attempt n.%d\n", attempt);
        WiFi.begin(info.ssid, info.key);
        if (WiFi.waitForConnectResult() == WL_CONNECTED) {
            return true;
        }
        delay(1000);
    }
    return false;
}


void ESPWifiManager::activateAPMode()
{
    const long APRand = random(APRAND_LOWER, APRAND_UPPER);
    char randSSID[SSID_LENGTH];
    snprintf(randSSID, sizeof(randSSID), "%s%d", AP_SSID, APRand);

    // Init ESP WiFi as AP
    WiFi.mode(WIFI_AP);
    WiFi.softAP(randSSID);
    apMode = true;
    apServer.begin();
}

ESPWifiManager WiFiManager;

