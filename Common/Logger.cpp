#include "Logger.h"
#include <iostream>
#include <mutex>

static std::mutex logMutex;

void Log(LogLevel level, const std::string& msg) {
    std::lock_guard<std::mutex> lock(logMutex);
    const char* lvl =
        level == LogLevel::INFO ? "INFO" :
        level == LogLevel::WARN ? "WARN" :
        level == LogLevel::ERROR ? "ERROR" : "DEBUG";
    std::cout << "[" << lvl << "] " << msg << std::endl;
}
