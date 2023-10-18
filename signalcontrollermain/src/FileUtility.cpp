#include "FileUtility.h"
#include "SD.h"

bool FileUtility::init() {
    bool success = SD.begin(SDCARD_SS_PIN);
    return success;
}

bool FileUtility::readJsonFromFile(const char *filename, DynamicJsonDocument &doc) {
    File file = SD.open(filename, FILE_READ);
    if (!file) {
        return false;
    }
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    doc.shrinkToFit();
    return error == DeserializationError::Ok;
}

bool FileUtility::writeJsonToFile(const char *filename, const DynamicJsonDocument &doc) {
    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        return false;
    }
    serializeJson(doc, file);
    file.close();
    return true;
}
