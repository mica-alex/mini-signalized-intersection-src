#include "OutputManager.h"
#include "Logger.h"

OutputManager outputManager;

///////// SETUP METHOD /////////
void setup() {
    // Initialize logging system
    Logger::init();

    // Initialize outputs
    OutputManager::init();
}

///////// LOOP METHOD /////////
void loop() {

}