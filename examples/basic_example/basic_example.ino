#include <EspWifiManager.h>

void setup() {
    // your setup
}

void loop() {
    if(WiFiManager.isConnected()) {
        // your logic here
    }
    // if you're here, AP mode is currently active
}