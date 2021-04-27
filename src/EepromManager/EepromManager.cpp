#include "EepromManager.hpp"

EepromManager EeManager;

void EepromManager::start() {
    if(started) {
        return;
    }
    EEPROM.begin(sizeof(ConnectionInfo));
    started = true;
}


void EepromManager::writeConnectionInfo(ConnectionInfo *info) {
    memcpy(&conninfo, info, sizeof(ConnectionInfo));
    writeConnToEeprom();
    conninfoStarted = true;
}


ConnectionInfo EepromManager::readConnectionInfo() {
    if (!conninfoStarted) {
        readConnFromEeprom(); 
        conninfoStarted = true;
    }
    return conninfo;
}


void EepromManager::readConnFromEeprom() {
    if(!conninfoStarted) {
        EEPROM.get(CONNINFO_ADDR, conninfo);
        conninfoStarted = true;
    }
}


void EepromManager::writeConnToEeprom() {
    EEPROM.put(CONNINFO_ADDR, conninfo);
    EEPROM.commit();
}
