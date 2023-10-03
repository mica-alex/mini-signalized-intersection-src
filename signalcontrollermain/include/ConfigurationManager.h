#include "ArduinoJson.h"
#include "SD.h"
#include <SPI.h>

class ConfigurationManager {
public:
    static void init();

    static bool loadOutputsConfig();

    static bool saveOutputsConfig(const JsonObject &outputsConfig);

    static JsonObject getOutputsConfig();

    static bool setFriendlyName(int slot, int port, const char *friendlyName);

    static const char *getFriendlyName(int slot, int port);

    static bool setMultipleFriendlyNames(const int slots[], const int ports[], const char *friendlyNames[], int count);

    static void getFriendlyNames(JsonObject &dest);


private:
    static bool loadConfigFile(const char *filename, DynamicJsonDocument &doc);

    static bool saveConfigFile(const char *filename, const DynamicJsonDocument &doc);

    static DynamicJsonDocument outputsDoc;
};
