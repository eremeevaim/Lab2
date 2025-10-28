#pragma once
#include <string>
#include <fstream>
#include <ctime>

class Logger {
private:
    std::ofstream logFile;
    static Logger* instance;

    Logger();

public:
    ~Logger();
    static Logger& getInstance();
    void log(const std::string& message);
    void logAction(const std::string& action, const std::string& details = "");
};