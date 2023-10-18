#ifndef CONSTANTS_H
#define CONSTANTS_H

// OUTPUT CONSTANTS
constexpr int SLOT_COUNT = 2;
constexpr int PORT_COUNT = 8;

// CONFIGURATION FILE CONSTANTS
constexpr int DYNAMIC_JSON_DOC_SIZE = 512; // Increase size if necessary
constexpr const char *OUTPUTS_CONFIG_FILE_NAME = "outputs.json";
constexpr const char *TIMINGS_CONFIG_FILE_NAME = "timings.json";
constexpr const char *MODE_FILES_FOLDER_NAME = "modes";
constexpr const char *TIMINGS_CONFIG_FLASH_RATE_MS_KEY = "flashRateMs";
constexpr const char *TIMINGS_CONFIG_ALL_RED_TIME_MS_KEY = "allRedTimeMs";
constexpr const char *TIMINGS_CONFIG_NETWORK_STARTUP_TIMEOUT_MS_KEY = "networkStartupTimeoutMs";
constexpr int MAX_MODE_FILES = 10;

#endif // CONSTANTS_H
