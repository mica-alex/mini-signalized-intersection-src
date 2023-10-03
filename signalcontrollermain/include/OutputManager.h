#ifndef OUTPUT_MANAGER_H
#define OUTPUT_MANAGER_H

#include "P1AM.h"
#include "Constants.h"

class OutputManager {
public:
    static void init();

    void setOutput(boolean power, int slot, int point);

    boolean getOutput(int slot, int point);

private:
    static inline boolean state_powerStatus[SLOT_COUNT][PORT_COUNT] = {}; // Inline definition and initialization.
};

#endif // OUTPUT_MANAGER_H
