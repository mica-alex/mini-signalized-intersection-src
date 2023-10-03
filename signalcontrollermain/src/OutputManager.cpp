// OutputManager.cpp

#include "OutputManager.h"
#include "Logger.h"

void OutputManager::init() {
    // Initialize P1AM
    while (!P1.init()) {
        Logger::info(Logger::Type::STARTUP,
                     "P1AM not initialized. Checking again in 1 second...");
        delay(1000);
    }
}

void OutputManager::setOutput(boolean power, int slot, int point) {
    P1.writeDiscrete(power, slot, point);
    state_powerStatus[slot - 1][point - 1] = power;
}

boolean OutputManager::getOutput(int slot, int point) {
    return state_powerStatus[slot - 1][point - 1];
}
