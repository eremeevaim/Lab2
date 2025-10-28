#include "logger.h"
#include <iostream>

Logger* Logger::instance = nullptr;

Logger::Logger() {
    logFile.open("pipeline_log.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Не удалось открыть файл лога!" << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::getInstance() {
    if (!instance) {
        instance = new Logger();
    }
    return *instance;
}

void Logger::log(const std::string& message) {
    setlocale(LC_ALL, "RU");
    if (logFile.is_open()) {
        time_t now = time(nullptr);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now);
        std::string timeStr(buffer);
        timeStr.pop_back(); // удаляем символ новой строки

        logFile << timeStr << " - " << message << std::endl;
        logFile.flush();
    }

    // Также выводим в консоль
    std::cout << "[ЛОГ] " << message << std::endl;
}

void Logger::logAction(const std::string& action, const std::string& details) {
    std::string message = action;
    if (!details.empty()) {
        message += " - " + details;
    }
    log(message);
}