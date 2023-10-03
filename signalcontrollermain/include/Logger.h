#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    enum class Type {
        STARTUP,
        OPERATION,
        CONFIGURATION,
        OTHER
    };

    // Initialization method for the Serial
    static void init();

    // Logging methods
    static void debug(Type type, const char *message);

    static void info(Type type, const char *message);

    static void warn(Type type, const char *message);

    static void error(Type type, const char *message);

private:
    static void log(Level level, Type type, const char *message);

    static const char *levelToString(Level level);

    static const char *typeToString(Type type);
};

#endif // LOGGER_H
