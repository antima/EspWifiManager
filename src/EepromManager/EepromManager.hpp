#ifndef EEPROM_MANAGER_H_
#define EEPROM_MANAGER_H_

#include <EEPROM.h>
#include <stdint.h>

// conninfo defines
#define OK_LENGTH 1
#define SSID_LENGTH 32
#define KEY_LENGTH 64
#define BROKER_ADDR_LENGTH 16


#define CONN_INFO_LENGTH (OK_LENGTH+SSID_LENGTH+KEY_LENGTH)

// EEPROM defines
#define CONNINFO_ADDR 0
#define EEPROM_SIZE CONN_INFO_LENGTH


struct ConnectionInfo {
    bool ok;
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

extern EepromManager EepromManager;

#endif