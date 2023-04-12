#include <aWOT.h>
#include <SPI.h>
#include <Ethernet.h>
#include <P1AM.h>
#include <P1_HSC.h>

///////// SIGNAL CONTROL CONSTANTS /////////
const int signal_flashRateMs = 500;            // Rate of Signal Flash (Milliseconds)
const int signal_allRedTimeMs = 4000;          // Time of All Red Phase (Milliseconds)
const int signal_walkTimeMs = 30000;           // Time of Walk/Bike Phase (Milliseconds)
const int signal_flashDontWalkTimeMs = 10000;  // Time of Flash Dont Walk/Bike Phase (Milliseconds)
const int signal_yellowTimeMs = 4000;          // Time of Yellow Phase for Approach 1 (Milliseconds)
const int signal_minGreenTimeMs = 30000;       // Min Green Time for Approach 1 (Milliseconds)
const int signal_maxGreenTimeMs = 180000;      // Max Green Time for Approach 1 (if -1, a trigger such as walk button is required to properly cycle) (Milliseconds)

///////// SIGNAL WIRING CONSTANTS /////////
const int slotCount = 2;                // PLC Slot Count
const int pointPerSlotCount = 8;        // PLC Point per Slot Count
const int index_slot1 = 1;              // PLC Slot 1 Index
const int index_slot2 = 2;              // PLC Slot 2 Index
const int point_primaryArrowGreen = 1;  // PLC Slot Point for Primary Green Arrow
const int point_primaryArrowAmber = 8;  // PLC Slot Point for Primary Yellow Arrow
const int point_primaryYellow = 7;      // PLC Slot Point for Primary Yellow
const int point_primaryRed = 6;         // PLC Slot Point for Primary Red
const int point_primaryWalk = 1;        // PLC Slot Point for Primary Walk
const int point_primaryDontWalk = 2;    // PLC Slot Point for Primary Don't Walk
const int point_secondaryGreen = 5;     // PLC Slot Point for Secondary Green
const int point_secondaryYellow = 4;    // PLC Slot Point for Secondary Yellow
const int point_secondaryRed = 3;       // PLC Slot Point for Secondary Red
const int point_beacon = 2;             // PLC Slot Point for Beacon

///////// GPIO CONSTANTS /////////
const int gpio_primaryWalkButton = 4;         // GPIO Pin Index for Approach 1 Walk Button
const int gpio_controllerExternalSwitch = 6;  // GPIO Pin Index for Controller External Switch
const int gpio_controllerExternalPull = 7;    // GPIO Pin Index for Controller External Pull
const int gpio_controllerOnboardSwitch = 31;  // GPIO Pin Index for Controller Onboard Switch

///////// APPLICATION CONSTANTS /////////
const int application_loopRateMs = signal_flashRateMs;  // Rate of application loop (milliseconds)
const int application_maxEthernetWaitMs = 30000;        // Maximum Wait Time for Ethernet Link (milliseconds)

///////// NETWORK VARIABLES /////////
byte ethernet_macAddress[] = { 0x16, 0x75, 0x3F, 0x83, 0x22, 0xE9 };
byte ethernet_ip[] = { 10, 0, 0, 1 };
EthernetServer server(80);
Application app;

///////// STATE VARIABLES /////////
bool state_isFlashMode = true;
bool state_isPedEnabled = true;
bool state_isBeaconEnabled = false;
bool state_isWalkRequested = false;
bool state_phaseFlash = true;
int state_phaseIndex = 0;
int state_phaseMaxIndex = 6;
long int state_lastTime = 0;
int state_powerStatus[slotCount][pointPerSlotCount];
bool state_forcedOffMode = false;
bool state_forcedRedMode = false;
bool state_forcedYellowMode = false;
bool state_forcedGreenMode = false;

void setPointPower(int power, int slot, int point) {
  P1.writeDiscrete(power, slot, point);
  state_powerStatus[slot - 1][point - 1] = power;
}

void requestWalkCmd(Request &req, Response &res) {
  state_isWalkRequested = true;
  respondCmdSuccess(req, res);
}

void enablePedCmd(Request &req, Response &res) {
  state_isPedEnabled = true;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void disablePedCmd(Request &req, Response &res) {
  state_isPedEnabled = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void enableBeaconCmd(Request &req, Response &res) {
  state_isBeaconEnabled = true;
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
  respondCmdSuccess(req, res);
}

void disableBeaconCmd(Request &req, Response &res) {
  state_isBeaconEnabled = false;
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
  respondCmdSuccess(req, res);
}

void enableFlashCmd(Request &req, Response &res) {
  state_isFlashMode = true;
  state_forcedOffMode = false;
  state_forcedRedMode = false;
  state_forcedYellowMode = false;
  state_forcedGreenMode = false;
  state_isBeaconEnabled = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void disableFlashCmd(Request &req, Response &res) {
  state_isFlashMode = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void enableForcedOffCmd(Request &req, Response &res) {
  state_forcedOffMode = true;
  state_forcedRedMode = false;
  state_forcedYellowMode = false;
  state_forcedGreenMode = false;
  state_isFlashMode = false;
  state_isBeaconEnabled = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void disableForcedOffCmd(Request &req, Response &res) {
  state_forcedOffMode = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void enableForcedRedCmd(Request &req, Response &res) {
  state_forcedOffMode = false;
  state_forcedRedMode = true;
  state_forcedYellowMode = false;
  state_forcedGreenMode = false;
  state_isFlashMode = false;
  state_isBeaconEnabled = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void disableForcedRedCmd(Request &req, Response &res) {
  state_forcedRedMode = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void enableForcedYellowCmd(Request &req, Response &res) {
  state_forcedOffMode = false;
  state_forcedRedMode = false;
  state_forcedYellowMode = true;
  state_forcedGreenMode = false;
  state_isFlashMode = false;
  state_isBeaconEnabled = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void disableForcedYellowCmd(Request &req, Response &res) {
  state_forcedYellowMode = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void enableForcedGreenCmd(Request &req, Response &res) {
  state_forcedOffMode = false;
  state_forcedRedMode = false;
  state_forcedYellowMode = false;
  state_forcedGreenMode = true;
  state_isFlashMode = false;
  state_isBeaconEnabled = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void disableForcedGreenCmd(Request &req, Response &res) {
  state_forcedGreenMode = false;
  resetToStartPhase();
  respondCmdSuccess(req, res);
}

void respondCmdSuccess(Request &req, Response &res) {
  res.set("Content-Type", "application/json");
  res.set("Access-Control-Allow-Origin", "*");
  res.print("{\"success\":\"true\"}");
  res.end();
}

void respondCmdFailure(Request &req, Response &res) {
  res.set("Content-Type", "application/json");
  res.set("Access-Control-Allow-Origin", "*");
  res.print("{\"success\":\"false\"}");
  res.end();
}

void resetToStartPhase() {
  state_lastTime = 0;
  state_phaseFlash = true;
  state_phaseIndex = 0;
}

void getStateCmd(Request &req, Response &res) {
  res.set("Content-Type", "application/json");
  res.set("Access-Control-Allow-Origin", "*");
  res.print("{\"lamps\":[");
  for (int i = 0; i < slotCount; i++) {
    for (int j = 0; j < pointPerSlotCount; j++) {
      res.print("{\"slot\":");
      res.print((i + 1));
      res.print(",\"channel\":");
      res.print((j + 1));
      res.print(",\"powered\":");
      res.print(state_powerStatus[i][j] == HIGH ? "true" : "false");
      if ((i == slotCount - 1) && (j == pointPerSlotCount - 1)) {
        res.print("}]");
      } else {
        res.print("},");
      }
    }
  }
  res.print(",\"flashMode\":");
  res.print(state_isFlashMode ? "true" : "false");
  res.print(",\"walkRequested\":");
  res.print(state_isWalkRequested ? "true" : "false");
  res.print(",\"pedEnabled\":");
  res.print(state_isPedEnabled ? "true" : "false");
  res.print(",\"statePhaseFlash\":");
  res.print(state_phaseFlash);
  res.print(",\"statePhaseIndex\":");
  res.print(state_phaseIndex);
  res.print(",\"statePhaseMaxIndex\":");
  res.print(state_phaseMaxIndex);
  res.print(",\"stateForcedOffMode\":");
  res.print(state_forcedOffMode ? "true" : "false");
  res.print(",\"stateForcedRedMode\":");
  res.print(state_forcedRedMode ? "true" : "false");
  res.print(",\"stateForcedYellowMode\":");
  res.print(state_forcedYellowMode ? "true" : "false");
  res.print(",\"stateForcedGreenMode\":");
  res.print(state_forcedGreenMode ? "true" : "false");
  res.print(",\"stateIsBeaconEnabled\":");
  res.print(state_isBeaconEnabled ? "true" : "false");
  res.print(",\"stateLastTime\":");
  res.print(state_lastTime);
  res.println("}");
  res.end();
}


///////// SETUP METHOD /////////
void setup() {
  // Wait for P1 to initialize
  while (!P1.init()) {
  }

  // Configure ethernet port
  setPointPower(HIGH, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  int ethernetMaxWaitTime = millis() + application_maxEthernetWaitMs;
  delay(1000);
  while (Ethernet.linkStatus() != LinkON) {
    delay(500);
    if (millis() >= ethernetMaxWaitTime) {
      break;
    }
  }
  Ethernet.begin(ethernet_macAddress, ethernet_ip);
  app.get("/requestWalk", &requestWalkCmd);
  app.get("/enablePed", &enablePedCmd);
  app.get("/disablePed", &disablePedCmd);
  app.get("/enableBeacon", &enableBeaconCmd);
  app.get("/disableBeacon", &disableBeaconCmd);
  app.get("/enableFlash", &enableFlashCmd);
  app.get("/disableFlash", &disableFlashCmd);
  app.get("/enableForcedOffMode", &enableForcedOffCmd);
  app.get("/disableForcedOffMode", &disableForcedOffCmd);
  app.get("/enableForcedRedMode", &enableForcedRedCmd);
  app.get("/disableForcedRedMode", &disableForcedRedCmd);
  app.get("/enableForcedYellowMode", &enableForcedYellowCmd);
  app.get("/disableForcedYellowMode", &disableForcedYellowCmd);
  app.get("/enableForcedGreenMode", &enableForcedGreenCmd);
  app.get("/disableForcedGreenMode", &disableForcedGreenCmd);
  app.get("/getState", &getStateCmd);

  // Configure GPIO pin modes
  pinMode(gpio_controllerOnboardSwitch, INPUT);
  pinMode(gpio_controllerExternalSwitch, INPUT_PULLUP);
  pinMode(gpio_controllerExternalPull, INPUT_PULLUP);
  pinMode(gpio_primaryWalkButton, INPUT_PULLUP);

  // Set initial signal progamming values
  state_isFlashMode = digitalRead(gpio_controllerExternalSwitch);
  state_isBeaconEnabled = !digitalRead(gpio_controllerExternalPull);

  // Set bootup light and delay shortly before attaching interrupt
  setPointPower(LOW, index_slot1, point_secondaryRed);
  setPointPower(HIGH, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  delay(1000);

  // Configure interrupts for applicable GPIO pins
  attachInterrupt(digitalPinToInterrupt(gpio_controllerOnboardSwitch), controllerOnboardSwitchChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(gpio_controllerExternalSwitch), controllerExternalSwitchChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(gpio_controllerExternalPull), controllerExternalPullChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(gpio_primaryWalkButton), primaryWalkButtonPressed, FALLING);

  // Set bootup finish light and delay shortly before starting
  setPointPower(LOW, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(HIGH, index_slot1, point_secondaryGreen);
  delay(1000);

  // Set all red phase
  setAllRedPhaseWithDontWalkOrBike();
  state_lastTime = millis();
}

///////// LOOP METHOD /////////
void loop() {
  // Fault Mode (Forced Flash)
  if (Ethernet.linkStatus() == Unknown || Ethernet.linkStatus() == LinkOFF) {
    if (state_phaseFlash) {
      setFlashPhase();
    } else {
      setOffPhase();
    }
    state_lastTime = 0;
  }
  // Forced Off Mode
  else if (state_forcedOffMode) {
    setOffPhase();
  }
  // Forced Red Mode
  else if (state_forcedRedMode) {
    setAllRedPhaseWithDontWalkOrBike();
  }
  // Forced Yellow Mode
  else if (state_forcedYellowMode) {
    setYellowPhase();
  }
  // Forced Green Mode
  else if (state_forcedGreenMode) {
    setGreenPhase();
  }
  // Flash Mode
  else if (state_isFlashMode) {
    if (state_phaseFlash) {
      setFlashPhase();
    } else {
      setOffPhase();
    }
    state_lastTime = 0;
  }
  // Standard (Non-Flash) Mode
  else {
    bool didChangePhase = false;
    long int timeSinceLastChange = millis() - state_lastTime;

    // Handle state phase index 0 (All red 1)
    if (state_phaseIndex == 0) {
      // Check if phase is complete
      if (timeSinceLastChange > signal_allRedTimeMs && state_phaseFlash) {
        setGreenPhase();
        didChangePhase = true;
      }
    }
    // Handle state phase index 1 (Vehicular Green)
    else if (state_phaseIndex == 1) {
      // Check if phase is complete
      if (timeSinceLastChange > signal_minGreenTimeMs && state_phaseFlash && state_isWalkRequested) {
        setYellowPhase();
        didChangePhase = true;
      } else if (timeSinceLastChange > signal_maxGreenTimeMs && state_phaseFlash) {
        setYellowPhase();
        didChangePhase = true;
      }
    }
    // Handle state phase index 2 (Vehicular Yellow)
    else if (state_phaseIndex == 2) {
      // Check if phase is complete
      if (timeSinceLastChange > signal_yellowTimeMs && state_phaseFlash) {
        setAllRedPhaseWithDontWalkOrBike();
        didChangePhase = true;
      }
    }
    // Handle state phase index 3 (All Red 2)
    else if (state_phaseIndex == 3) {
      // Check if phase is complete
      if (timeSinceLastChange > signal_allRedTimeMs && state_phaseFlash) {
        setAllRedPhaseWithBikeWithWalk();
        didChangePhase = true;
      }
    }
    // Handle state phase index 4 (Vehicular Red w/ Ped+Bike Green)
    else if (state_phaseIndex == 4) {
      // Check if phase is complete
      if (timeSinceLastChange > signal_walkTimeMs && state_phaseFlash) {
        setAllRedPhaseWithBikeWithDontWalk();
        didChangePhase = true;
      }
    }
    // Handle state phase index 5 (Vehicular Red w/ Flash Ped+Bike Green)
    else if (state_phaseIndex == 5) {
      // Check if phase is complete
      if (timeSinceLastChange > signal_flashDontWalkTimeMs && state_phaseFlash) {
        setAllRedPhaseWithYellowBikeWithDontWalk();
        didChangePhase = true;
      }
      // Flash dont walk if phase continuing
      else {
        if (state_phaseFlash) {
          setAllRedPhaseWithBikeWithDontWalk();
        } else {
          setAllRedPhaseWithBikeWithoutWalk();
        }

        // Clear walk requested if within 1 second
        if (timeSinceLastChange < 1000) {
          state_isWalkRequested = false;
        }
      }
    }
    // Handle state phase index 6 (Vehicular Red w/ Flash Ped+Bike Yellow)
    else if (state_phaseIndex == 6) {
      // Check if phase is complete
      if (timeSinceLastChange > signal_yellowTimeMs && state_phaseFlash) {
        setAllRedPhaseWithDontWalkOrBike();
        didChangePhase = true;
      }
      // Flash dont walk if phase continuing
      else {
        if (state_phaseFlash) {
          setAllRedPhaseWithYellowBikeWithDontWalk();
        } else {
          setAllRedPhaseWithYellowBikeWithoutWalk();
        }
      }
    }

    // Update phase index and last time
    if (didChangePhase) {
      state_lastTime = millis();
      state_phaseIndex = state_phaseIndex + 1;
      // Check if phase index past max (state_phaseMaxIndex)
      if (state_phaseIndex > state_phaseMaxIndex) {
        state_phaseIndex = 0;
      }
    }
  }

  // Flip state flash boolean
  state_phaseFlash = !state_phaseFlash;

  // Sleep for loop time and process network requests
  long int delayTimeEndMs = millis() + application_loopRateMs;
  while (millis() < delayTimeEndMs) {
    // Process network requests
    EthernetClient client = server.available();
    if (client.connected()) {
      app.process(&client);
      client.stop();
    }
  }
}

///////// CONTROLLER ONBOARD SWITCH CHANGE METHOD /////////
void controllerOnboardSwitchChange() {
  state_isPedEnabled = digitalRead(gpio_controllerOnboardSwitch);
}

///////// CONTROLLER EXTERNAL SWITCH CHANGE METHOD /////////
void controllerExternalSwitchChange() {
  state_isFlashMode = digitalRead(gpio_controllerExternalSwitch);
  state_phaseFlash = true;
}

///////// CONTROLLER EXTERNAL PULL CHANGE METHOD /////////
void controllerExternalPullChange() {
  state_isBeaconEnabled = !digitalRead(gpio_controllerExternalPull);
}

///////// PRIMARY WALK BTN PRESSED (RISING) METHOD /////////
void primaryWalkButtonPressed() {
  state_isWalkRequested = true;
}

///////// GREEN PHASE METHOD /////////
void setGreenPhase() {
  setPointPower(LOW, index_slot1, point_primaryWalk);
  setPointPower(state_isPedEnabled ? HIGH : LOW, index_slot1, point_primaryDontWalk);
  setPointPower(LOW, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(HIGH, index_slot1, point_secondaryGreen);
  setPointPower(HIGH, index_slot1, point_primaryRed);
  setPointPower(LOW, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(LOW, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// YELLOW PHASE METHOD /////////
void setYellowPhase() {
  setPointPower(LOW, index_slot1, point_primaryWalk);
  setPointPower(state_isPedEnabled ? HIGH : LOW, index_slot1, point_primaryDontWalk);
  setPointPower(LOW, index_slot1, point_secondaryRed);
  setPointPower(HIGH, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(HIGH, index_slot1, point_primaryRed);
  setPointPower(LOW, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(LOW, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// ALL RED PHASE (WALK/BIKE) METHOD /////////
void setAllRedPhaseWithBikeWithWalk() {
  setPointPower(state_isPedEnabled ? HIGH : LOW, index_slot1, point_primaryWalk);
  setPointPower(LOW, index_slot1, point_primaryDontWalk);
  setPointPower(HIGH, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(LOW, index_slot1, point_primaryRed);
  setPointPower(LOW, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(HIGH, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// ALL RED PHASE (WALK/YELLOW BIKE) METHOD /////////
void setAllRedPhaseWithYellowBikeWithWalk() {
  setPointPower(state_isPedEnabled ? HIGH : LOW, index_slot1, point_primaryWalk);
  setPointPower(LOW, index_slot1, point_primaryDontWalk);
  setPointPower(HIGH, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(LOW, index_slot1, point_primaryRed);
  setPointPower(HIGH, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(LOW, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// ALL RED PHASE (DONT WALK OR BIKE) METHOD /////////
void setAllRedPhaseWithDontWalkOrBike() {
  setPointPower(LOW, index_slot1, point_primaryWalk);
  setPointPower(state_isPedEnabled ? HIGH : LOW, index_slot1, point_primaryDontWalk);
  setPointPower(HIGH, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(HIGH, index_slot1, point_primaryRed);
  setPointPower(LOW, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(LOW, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// ALL RED PHASE (GREEN BIKE WITH DONT WALK) METHOD /////////
void setAllRedPhaseWithBikeWithDontWalk() {
  setPointPower(LOW, index_slot1, point_primaryWalk);
  setPointPower(state_isPedEnabled ? HIGH : LOW, index_slot1, point_primaryDontWalk);
  setPointPower(HIGH, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(LOW, index_slot1, point_primaryRed);
  setPointPower(LOW, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(HIGH, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// ALL RED PHASE (DONT WALK W/ YELLOW BIKE) METHOD /////////
void setAllRedPhaseWithYellowBikeWithDontWalk() {
  setPointPower(LOW, index_slot1, point_primaryWalk);
  setPointPower(state_isPedEnabled ? HIGH : LOW, index_slot1, point_primaryDontWalk);
  setPointPower(HIGH, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(LOW, index_slot1, point_primaryRed);
  setPointPower(HIGH, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(LOW, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// ALL RED PHASE (WITH BIKE, WITHOUT WALK/DONT WALK) METHOD /////////
void setAllRedPhaseWithBikeWithoutWalk() {
  setPointPower(LOW, index_slot1, point_primaryWalk);
  setPointPower(LOW, index_slot1, point_primaryDontWalk);
  setPointPower(HIGH, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(LOW, index_slot1, point_primaryRed);
  setPointPower(LOW, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(HIGH, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// ALL RED PHASE (WITH YELLOW BIKE, WITHOUT WALK/DONT WALK) METHOD /////////
void setAllRedPhaseWithYellowBikeWithoutWalk() {
  setPointPower(LOW, index_slot1, point_primaryWalk);
  setPointPower(LOW, index_slot1, point_primaryDontWalk);
  setPointPower(HIGH, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(LOW, index_slot1, point_primaryRed);
  setPointPower(HIGH, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(LOW, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// FLASH PHASE METHOD /////////
void setFlashPhase() {
  setPointPower(LOW, index_slot1, point_primaryWalk);
  setPointPower(LOW, index_slot1, point_primaryDontWalk);
  setPointPower(LOW, index_slot1, point_secondaryRed);
  setPointPower(HIGH, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(HIGH, index_slot1, point_primaryRed);
  setPointPower(LOW, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(LOW, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}

///////// OFF PHASE METHOD /////////
void setOffPhase() {
  setPointPower(LOW, index_slot1, point_primaryWalk);
  setPointPower(LOW, index_slot1, point_primaryDontWalk);
  setPointPower(LOW, index_slot1, point_secondaryRed);
  setPointPower(LOW, index_slot1, point_secondaryYellow);
  setPointPower(LOW, index_slot1, point_secondaryGreen);
  setPointPower(LOW, index_slot1, point_primaryRed);
  setPointPower(LOW, index_slot1, point_primaryYellow);
  setPointPower(LOW, index_slot1, point_primaryArrowAmber);
  setPointPower(LOW, index_slot2, point_primaryArrowGreen);
  setPointPower(state_isBeaconEnabled ? HIGH : LOW, index_slot2, point_beacon);
}