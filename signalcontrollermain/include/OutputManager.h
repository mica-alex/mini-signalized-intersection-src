#ifndef OUTPUT_MANAGER_H
#define OUTPUT_MANAGER_H

#include "P1AM.h"
#include "Constants.h"

class OutputManager {
public:
    static bool init();

    static void setOutput(boolean power, int slot, int point);

    static boolean getOutput(int slot, int point);

private:
    static inline boolean state_powerStatus[SLOT_COUNT][PORT_COUNT] = {};
};

#endif // OUTPUT_MANAGER_H
