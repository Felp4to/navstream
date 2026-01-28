#pragma once
#include <string>

enum class LogLevel {
    INFO,
    WARN,
    ERROR,
    DEBUG
};

void Log(LogLevel level, const std::string& msg);

#define LOG_INFO(msg)  Log(LogLevel::INFO,  msg)
#define LOG_WARN(msg)  Log(LogLevel::WARN,  msg)
#define LOG_ERROR(msg) Log(LogLevel::ERROR, msg)
#define LOG_DEBUG(msg) Log(LogLevel::DEBUG, msg)