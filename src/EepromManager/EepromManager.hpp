#ifndef EEPROM_MANAGER_H_
#define EEPROM_MANAGER_H_

#include <EEPROM.h>
#include <stdint.h>

// conninfo defines
#define SSID_LENGTH 32
#define KEY_LENGTH 64

// EEPROM defines
#define CONNINFO_ADDR 0


struct ConnectionInfo {
    char ssid[SSID_LENGTH];
    char key[KEY_LENGTH];
};


class EepromManager {
    private:
        bool started;
        bool conninfoStarted;
        ConnectionInfo conninfo;

        void readConnFromEeprom();
        void writeConnToEeprom();

    public:
        void start();
        void writeConnectionInfo(ConnectionInfo*);
        ConnectionInfo readConnectionInfo();

        EepromManager() : started(false), conninfoStarted(false), conninfo{} {};
        ~EepromManager(){};
};

extern EepromManager EeManager;

#endif