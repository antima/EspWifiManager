#include <stdio.h>
#include "EspWifiManager.h"
#include "EepromManager/EepromManager.hpp"

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

