#pragma once
#include <iostream>
#include <string>
#include <limits>

// Ћогирование
void logAction(const std::string& action);

// ¬вод данных
std::string getStringInput();
int getIntInput();
double getDoubleInput();
bool getYesNoInput();

// ¬вод с проверками
int getPositiveInt();
double getPositiveDouble();
int getIntInRange(int min, int max);

// ќчистка буфера
void clearInputBuffer();