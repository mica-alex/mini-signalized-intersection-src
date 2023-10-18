#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include "ArduinoJson.h"
#include "SD.h"
#include "Constants.h"
#include <SPI.h>

class ConfigurationManager {
public:
    static bool init();

    static bool loadOutputsConfig();

    static bool saveOutputsConfig(const JsonObject &outputsConfig);

    static JsonObject getOutputsConfig();

    static bool setOutputFriendlyName(int slot, int port, const char *friendlyName);

    static const char *getOutputFriendlyName(int slot, int port);

    static bool setOutputsFriendlyNames(const int slots[], const int ports[], const char *friendlyNames[], int count);

    static void getOutputsFriendlyNames(JsonObject &dest);

    static bool loadTimingsConfig();

    static bool saveTimingsConfig(const JsonObject &timingsConfig);

    static JsonObject getTimingsConfig();

    static long getFlashRateMs();

    static long getAllRedTimeMs();

    static long getNetworkStartupTimeoutMs();

    static bool setFlashRateMs(long flashRateMs);

    static bool setAllRedTimeMs(long allRedTimeMs);

    static bool setNetworkStartupTimeoutMs(long networkStartupTimeoutMs);

    static bool setTimingsConfig(const JsonObject &timingsConfig);

    static bool setTimingsConfig(long flashRateMs, long allRedTimeMs, long networkStartupTimeoutMs);


private:
    static inline DynamicJsonDocument outputsDoc = DynamicJsonDocument(DYNAMIC_JSON_DOC_SIZE);

    static inline DynamicJsonDocument timingsDoc = DynamicJsonDocument(DYNAMIC_JSON_DOC_SIZE);
};

#endif // CONFIGURATION_MANAGER_H