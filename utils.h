#pragma once
#include <string>
#include <iostream>

bool isInteger(const std::string& s);
int getIntegerInput(const std::string& prompt, int minVal, int maxVal);
double getDoubleInput(const std::string& prompt, double minVal, double maxVal);
bool getYesNoInput(const std::string& prompt);
std::string getStringInput(const std::string& prompt);
void clearInputBuffer();