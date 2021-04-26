# EspWifiManager

A simple credential manager that takes care of the boring part of writing Wifi-based sketches on ESP: the WiFi setup boilerplate. 

## Contents
  - [About](#about) 
  - [Installation](#installation-arduino-ide)
  - [How To](#how-to)


## About

This library manages your WiFi connection by doing two things:

- It auto-connects to the last WiFi network saved in the ESP non-volatile memory;
- It lets you input your WiFi connecton credentials via a browser-based interface;
  
By doing this, you don't have to re-flash your firmware every time you change WiFi network and you don't have to include your credentials into your code as hardcoded variables.

## Installation (Arduino IDE)

Clone this repository into your Arduino libraries folder, or click download zip from the upper right corner of this github page if you want to have a release with the latest features.

If you want download the zip version, you can add it to your environment by clicking Sketch -> Include Library -> Add -> .ZIP Library... and selecting the zip file you just downloaded.

## How to

```c++
#include <EspWifiManager.h>

void setup() {
    // your setup
}

void loop() {
    if(ESPWifiManager.isConnected())
    {
        // your logic here
    }
}
```