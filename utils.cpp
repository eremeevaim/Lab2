#include "utils.h"
#include <sstream>

bool isInteger(const std::string& s) {
    std::istringstream iss(s);
    int num;
    iss >> num;
    return !iss.fail() && iss.eof();
}

int getIntegerInput(const std::string& prompt, int minVal, int maxVal) {
    setlocale(LC_ALL, "RU");
    std::string input;
    int value;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (isInteger(input)) {
            std::stringstream ss(input);
            ss >> value;
            if (value >= minVal && value <= maxVal) {
                return value;
            }
        }
        std::cout << "Неверный ввод. Пожалуйста, введите целое число от "
            << minVal << " до " << maxVal << ".\n";
    }
}

double getDoubleInput(const std::string& prompt, double minVal, double maxVal) {
    setlocale(LC_ALL, "RU");
    std::string input;
    double value;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        std::stringstream ss(input);
        if (ss >> value && value >= minVal && value <= maxVal) {
            return value;
        }
        std::cout << "Неверный ввод. Пожалуйста, введите число от "
            << minVal << " до " << maxVal << ".\n";
    }
}

bool getYesNoInput(const std::string& prompt) {
    setlocale(LC_ALL, "RU");
    std::string input;

    while (true) {
        std::cout << prompt << " (д/н): ";
        std::getline(std::cin, input);

        if (input == "д" || input == "Д" || input == "y" || input == "Y" || input == "да") {
            return true;
        }
        else if (input == "н" || input == "Н" || input == "n" || input == "N" || input == "нет") {
            return false;
        }
        std::cout << "Пожалуйста, введите 'д' или 'н'.\n";
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}