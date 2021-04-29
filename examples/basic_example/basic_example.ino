#include <EspWifiManager.h>

void setup() {
    // your setup
}

void loop() {
    WiFiManager.loop(); // call this in the loop function
    if(WiFiManager.isConnected())
    {
        // this is executed if the ESP is connected
        // to the network
    }
}