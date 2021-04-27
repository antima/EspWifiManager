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
