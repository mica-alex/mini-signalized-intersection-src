#include "ModeManager.h"

std::vector<String> ModeManager::availableModeNames;
String ModeManager::activeModeName = "";
DynamicJsonDocument ModeManager::activeModeDoc(1024); // Or whatever size you deem appropriate.

bool ModeManager::init() {
    File root = SD.open(MODE_FILES_FOLDER_NAME);
    if (!root) {
        return false;  // Unable to open the directory
    }

    File fileEntry = root.openNextFile();
    while (fileEntry) {
        if (!fileEntry.isDirectory()) {
            availableModeNames.push_back(fileEntry.name());
        }
        fileEntry = root.openNextFile(); // Move to next file
    }

    fileEntry.close();
    root.close();
    return true; // Successfully initialized
}

bool ModeManager::setActiveMode(const String& modeName) {
    DynamicJsonDocument doc(1024); // Assuming this size is sufficient. Adjust if needed.
    String filePath = String(MODE_FILES_FOLDER_NAME) + "/" + modeName;
    if (!FileUtility::readJsonFromFile(filePath.c_str(), doc)) {
        return false;
    }
    activeModeDoc = doc;
    activeModeName = modeName;
    return true;
}

String ModeManager::getActiveMode() {
    return activeModeName;
}

std::vector<String> ModeManager::getAvailableModes() {
    return availableModeNames;
}
