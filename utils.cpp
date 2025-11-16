#include "utils.h"
#include <fstream>

void logAction(const std::string& action) {
    static std::ofstream logFile("actions.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << action << "\n";  // Просто действие, без времени
    }
    std::cout << "[ЛОГ] " << action << "\n";
}

std::string getStringInput() {
    std::string input;
    std::getline(std::cin, input);

    // Базовая проверка на пустоту
    if (input.empty()) {
        std::cout << "Ввод не может быть пустым. Попробуйте снова: ";
        return getStringInput();
    }
    return input;
}

int getIntInput() {
    int value;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        clearInputBuffer();
        std::cout << "Ошибка! Введите целое число: ";
        return getIntInput();
    }
    clearInputBuffer();
    return value;
}

double getDoubleInput() {
    double value;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        clearInputBuffer();
        std::cout << "Ошибка! Введите число: ";
        return getDoubleInput();
    }
    clearInputBuffer();
    return value;
}

bool getYesNoInput() {
    int input = getIntInput();
    if (input == 0 || input == 1) {
        return input == 1;
    }
    std::cout << "Введите 1 (да) или 0 (нет): ";
    return getYesNoInput();
}

int getPositiveInt() {
    int value = getIntInput();
    if (value <= 0) {
        std::cout << "Число должно быть положительным. Попробуйте снова: ";
        return getPositiveInt();
    }
    return value;
}

double getPositiveDouble() {
    double value = getDoubleInput();
    if (value <= 0) {
        std::cout << "Число должно быть положительным. Попробуйте снова: ";
        return getPositiveDouble();
    }
    return value;
}

int getIntInRange(int min, int max) {
    int value = getIntInput();
    if (value < min || value > max) {
        std::cout << "Число должно быть от " << min << " до " << max << ": ";
        return getIntInRange(min, max);
    }
    return value;
}

void clearInputBuffer() {
    std::cin.ignore(10000, '\n');  // Простая очистка
}