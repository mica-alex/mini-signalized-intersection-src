#include "ConfigurationManager.h"
#include "Constants.h"

DynamicJsonDocument ConfigurationManager::outputsDoc(512); // Increase size if necessary

void ConfigurationManager::init() {
    SD.begin(SDCARD_SS_PIN);
    loadOutputsConfig();
}

bool ConfigurationManager::loadConfigFile(const char *filename, DynamicJsonDocument &doc) {
    File file = SD.open(filename, FILE_READ);
    if (!file) {
        return false;
    }
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    doc.shrinkToFit();  // minimize memory footprint
    return error == DeserializationError::Ok;
}

bool ConfigurationManager::saveConfigFile(const char *filename, const DynamicJsonDocument &doc) {
    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        return false;
    }
    serializeJson(doc, file);
    file.close();
    return true;
}

bool ConfigurationManager::loadOutputsConfig() {
    return loadConfigFile(OUTPUTS_CONFIG_FILE_NAME, outputsDoc);
}

bool ConfigurationManager::saveOutputsConfig(const JsonObject &outputsConfig) {
    DynamicJsonDocument newDoc(512);
    newDoc.as<JsonObject>().set(outputsConfig);
    return saveConfigFile(OUTPUTS_CONFIG_FILE_NAME, newDoc);
}

JsonObject ConfigurationManager::getOutputsConfig() {

    return outputsDoc.as<JsonObject>();
}

bool ConfigurationManager::setFriendlyName(int slot, int port, const char *friendlyName) {
    JsonObject slotObj = outputsDoc[String(slot)];
    if (friendlyName == nullptr || strlen(friendlyName) == 0) {
        slotObj.remove(String(port));
    } else {
        slotObj[String(port)] = friendlyName;
    }
    return saveOutputsConfig(outputsDoc.as<JsonObject>());
}

const char *ConfigurationManager::getFriendlyName(int slot, int port) {
    return outputsDoc[String(slot)][String(port)];
}

bool ConfigurationManager::setMultipleFriendlyNames(const int slots[], const int ports[], const char *friendlyNames[],
                                                    int count) {
    for (int i = 0; i < count; i++) {
        setFriendlyName(slots[i], ports[i], friendlyNames[i]);
    }
    return saveOutputsConfig(outputsDoc.as<JsonObject>());
}

void ConfigurationManager::getFriendlyNames(JsonObject &dest) {
    dest = outputsDoc.as<JsonObject>();
}

