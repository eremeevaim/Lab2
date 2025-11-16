#pragma once
#include <string>
#include <iostream>

class Station {
private:
    static int nextId;
    int id;
    std::string name;
    int totalWorkshops;
    int workingWorkshops;

public:
    Station();
    Station(const std::string& name, int total, int working);

    // Геттеры
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getTotalWorkshops() const { return totalWorkshops; }
    int getWorkingWorkshops() const { return workingWorkshops; }

    // Расчеты
    double getUnusedPercentage() const;
    int getUnusedCount() const { return totalWorkshops - workingWorkshops; }

    // Сеттеры
    void setName(const std::string& newName) { name = newName; }
    void setTotalWorkshops(int total);
    void setWorkingWorkshops(int working);

    // Ввод/вывод
    void readFromConsole();
    void printToConsole() const;

    // Сохранение/загрузка
    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);
};