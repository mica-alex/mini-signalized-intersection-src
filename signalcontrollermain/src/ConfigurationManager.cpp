#include "ConfigurationManager.h"
#include "Constants.h"
#include "FileUtility.h"

bool ConfigurationManager::init() {
    bool success = SD.begin(SDCARD_SS_PIN);
    success &= loadOutputsConfig();
    success &= loadTimingsConfig();
    return success;
}

bool ConfigurationManager::loadOutputsConfig() {
    return FileUtility::readJsonFromFile(OUTPUTS_CONFIG_FILE_NAME, outputsDoc);
}

bool ConfigurationManager::saveOutputsConfig(const JsonObject &outputsConfig) {
    DynamicJsonDocument newDoc(DYNAMIC_JSON_DOC_SIZE);
    newDoc.as<JsonObject>().set(outputsConfig);
    return FileUtility::writeJsonToFile(OUTPUTS_CONFIG_FILE_NAME, newDoc);
}

JsonObject ConfigurationManager::getOutputsConfig() {
    return outputsDoc.as<JsonObject>();
}

bool ConfigurationManager::setOutputFriendlyName(int slot, int port, const char *friendlyName) {
    JsonObject slotObj = outputsDoc[String(slot)];
    if (friendlyName == nullptr || strlen(friendlyName) == 0) {
        slotObj.remove(String(port));
    } else {
        slotObj[String(port)] = friendlyName;
    }
    return saveOutputsConfig(outputsDoc.as<JsonObject>());
}

const char *ConfigurationManager::getOutputFriendlyName(int slot, int port) {
    return outputsDoc[String(slot)][String(port)];
}

bool ConfigurationManager::setOutputsFriendlyNames(const int slots[], const int ports[], const char *friendlyNames[],
                                                   int count) {
    for (int i = 0; i < count; i++) {
        setOutputFriendlyName(slots[i], ports[i], friendlyNames[i]);
    }
    return saveOutputsConfig(outputsDoc.as<JsonObject>());
}

void ConfigurationManager::getOutputsFriendlyNames(JsonObject &dest) {
    dest = outputsDoc.as<JsonObject>();
}

bool ConfigurationManager::loadTimingsConfig() {
    bool success = FileUtility::readJsonFromFile(TIMINGS_CONFIG_FILE_NAME, timingsDoc);
    if (success && !timingsDoc.containsKey(TIMINGS_CONFIG_FLASH_RATE_MS_KEY)) {
        success = false;
    } else if (success && !timingsDoc.containsKey(TIMINGS_CONFIG_ALL_RED_TIME_MS_KEY)) {
        success = false;
    } else if (success && !timingsDoc.containsKey(TIMINGS_CONFIG_NETWORK_STARTUP_TIMEOUT_MS_KEY)) {
        success = false;
    }
    return success;
}

bool ConfigurationManager::saveTimingsConfig(const JsonObject &timingsConfig) {
    DynamicJsonDocument newDoc(DYNAMIC_JSON_DOC_SIZE);
    newDoc.as<JsonObject>().set(timingsConfig);
    return FileUtility::writeJsonToFile(TIMINGS_CONFIG_FILE_NAME, newDoc);
}

JsonObject ConfigurationManager::getTimingsConfig() {
    return outputsDoc.as<JsonObject>();
}

long ConfigurationManager::getFlashRateMs() {
    return outputsDoc[TIMINGS_CONFIG_FLASH_RATE_MS_KEY];
}

long ConfigurationManager::getAllRedTimeMs() {
    return outputsDoc[TIMINGS_CONFIG_ALL_RED_TIME_MS_KEY];
}

long ConfigurationManager::getNetworkStartupTimeoutMs() {
    return outputsDoc[TIMINGS_CONFIG_NETWORK_STARTUP_TIMEOUT_MS_KEY];
}

bool ConfigurationManager::setFlashRateMs(long flashRateMs) {
    outputsDoc[TIMINGS_CONFIG_FLASH_RATE_MS_KEY] = flashRateMs;
    return saveTimingsConfig(outputsDoc.as<JsonObject>());
}

bool ConfigurationManager::setAllRedTimeMs(long allRedTimeMs) {
    outputsDoc[TIMINGS_CONFIG_ALL_RED_TIME_MS_KEY] = allRedTimeMs;
    return saveTimingsConfig(outputsDoc.as<JsonObject>());
}

bool ConfigurationManager::setNetworkStartupTimeoutMs(long networkStartupTimeoutMs) {
    outputsDoc[TIMINGS_CONFIG_NETWORK_STARTUP_TIMEOUT_MS_KEY] = networkStartupTimeoutMs;
    return saveTimingsConfig(outputsDoc.as<JsonObject>());
}

bool ConfigurationManager::setTimingsConfig(const JsonObject &timingsConfig) {
    DynamicJsonDocument newDoc(DYNAMIC_JSON_DOC_SIZE);
    newDoc.as<JsonObject>().set(timingsConfig);
    return saveTimingsConfig(newDoc.as<JsonObject>());
}

bool ConfigurationManager::setTimingsConfig(long flashRateMs, long allRedTimeMs, long networkStartupTimeoutMs) {
    outputsDoc[TIMINGS_CONFIG_FLASH_RATE_MS_KEY] = flashRateMs;
    outputsDoc[TIMINGS_CONFIG_ALL_RED_TIME_MS_KEY] = allRedTimeMs;
    outputsDoc[TIMINGS_CONFIG_NETWORK_STARTUP_TIMEOUT_MS_KEY] = networkStartupTimeoutMs;
    return saveTimingsConfig(outputsDoc.as<JsonObject>());
}