#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

#include <Arduino.h>
#include <SD.h>
#include <ArduinoJson.h>
#include "FileUtility.h"
#include "Constants.h"
#include <vector>

class ModeManager {
public:
    static bool init();
    static bool setActiveMode(const String& modeName);
    static String getActiveMode();
    static std::vector<String> getAvailableModes();

private:
    static std::vector<String> availableModeNames;
    static String activeModeName;
    static DynamicJsonDocument activeModeDoc;
};

#endif // MODE_MANAGER_H
