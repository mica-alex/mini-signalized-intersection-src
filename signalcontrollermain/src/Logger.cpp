#include "Logger.h"

void Logger::init() {
    Serial.begin(115200);
    Serial.println("Logger initialized. System starting...");
}

void Logger::debug(Type type, const char *message) {
    log(Level::DEBUG, type, message);
}

void Logger::info(Type type, const char *message) {
    log(Level::INFO, type, message);
}

void Logger::warn(Type type, const char *message) {
    log(Level::WARN, type, message);
}

void Logger::error(Type type, const char *message) {
    log(Level::ERROR, type, message);
}

void Logger::log(Level level, Type type, const char *message) {
    Serial.print("[");
    Serial.print(typeToString(type));
    Serial.print("/");
    Serial.print(levelToString(level));
    Serial.print("] ");
    Serial.println(message);
}

const char *Logger::levelToString(Level level) {
    switch (level) {
        case Level::DEBUG:
            return "DEBUG";
        case Level::INFO:
            return "INFO";
        case Level::WARN:
            return "WARN";
        case Level::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

const char *Logger::typeToString(Type type) {
    switch (type) {
        case Type::STARTUP:
            return "STARTUP";
        case Type::OPERATION:
            return "OPERATION";
        case Type::CONFIGURATION:
            return "CONFIGURATION";
        case Type::OTHER:
            return "OTHER";
        default:
            return "UNKNOWN";
    }
}
