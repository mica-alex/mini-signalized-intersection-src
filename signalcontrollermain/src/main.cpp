#include "OutputManager.h"
#include "Logger.h"
#include "ConfigurationManager.h"
#include "FileUtility.h"
#include "ModeManager.h"

OutputManager outputManager;
bool setupSuccess;

///////// SETUP METHOD /////////
void setup() {
    // Initialize logging system
    Logger::init();

    // Initialize file system
    setupSuccess = FileUtility::init();

    // Initialize outputs
    setupSuccess = OutputManager::init();

    // Initialize mode manager
    setupSuccess &= ModeManager::init();

    // Initialize configuration manager
    setupSuccess &= ConfigurationManager::init();

    // Log whether setup was successful
    if (setupSuccess) {
        Logger::info(Logger::Type::STARTUP, "Setup successful.");
    } else {
        Logger::error(Logger::Type::STARTUP, "Setup failed.");
    }
}

///////// LOOP METHOD /////////
void loop() {

}