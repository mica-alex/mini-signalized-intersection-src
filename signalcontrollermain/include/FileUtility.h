#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H

#include "ArduinoJson.h"
#include "P1AM.h"
#include "Constants.h"

class FileUtility {
public:
    static bool init();

    static bool readJsonFromFile(const char *filename, DynamicJsonDocument &doc);

    static bool writeJsonToFile(const char *filename, const DynamicJsonDocument &doc);
};

#endif // FILE_UTILITY_H
