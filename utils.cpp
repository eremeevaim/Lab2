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
        std::cout << "�������� ����. ����������, ������� ����� ����� �� "
            << minVal << " �� " << maxVal << ".\n";
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
        std::cout << "�������� ����. ����������, ������� ����� �� "
            << minVal << " �� " << maxVal << ".\n";
    }
}

bool getYesNoInput(const std::string& prompt) {
    setlocale(LC_ALL, "RU");
    std::string input;

    while (true) {
        std::cout << prompt << " (�/�): ";
        std::getline(std::cin, input);

        if (input == "�" || input == "�" || input == "y" || input == "Y" || input == "��") {
            return true;
        }
        else if (input == "�" || input == "�" || input == "n" || input == "N" || input == "���") {
            return false;
        }
        std::cout << "����������, ������� '�' ��� '�'.\n";
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