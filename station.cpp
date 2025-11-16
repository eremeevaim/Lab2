#include "station.h"
#include "utils.h"

int Station::nextId = 1;

Station::Station() : id(nextId++), name("Станция"), totalWorkshops(5), workingWorkshops(3) {}

Station::Station(const std::string& name, int total, int working)
    : id(nextId++), name(name), totalWorkshops(total), workingWorkshops(working) {
}

double Station::getUnusedPercentage() const {
    if (totalWorkshops == 0) return 0.0;
    return (getUnusedCount() * 100.0) / totalWorkshops;
}

void Station::setTotalWorkshops(int total) {
    if (total >= 0) {
        totalWorkshops = total;
        if (workingWorkshops > totalWorkshops) {
            workingWorkshops = totalWorkshops;
        }
    }
}

void Station::setWorkingWorkshops(int working) {
    if (working >= 0 && working <= totalWorkshops) {
        workingWorkshops = working;
    }
}

void Station::readFromConsole() {
    std::cout << "Добавление станции (ID: " << id << ")\n";

    std::cout << "Название: ";
    name = getStringInput();

    std::cout << "Всего цехов: ";
    totalWorkshops = getPositiveInt();

    std::cout << "Работающих цехов: ";
    workingWorkshops = getIntInRange(0, totalWorkshops);
}

void Station::printToConsole() const {
    std::cout << "=== Станция ID: " << id << " ===\n";
    std::cout << "Название: " << name << "\n";
    std::cout << "Всего цехов: " << totalWorkshops << "\n";
    std::cout << "Работающих: " << workingWorkshops << "\n";
    std::cout << "Незадействовано: " << getUnusedCount() << " ("
        << getUnusedPercentage() << "%)\n\n";
}

void Station::saveToFile(std::ostream& out) const {
    out << id << "\n" << name << "\n" << totalWorkshops << "\n" << workingWorkshops << "\n";
}

void Station::loadFromFile(std::istream& in) {
    in >> id;
    in.ignore();
    std::getline(in, name);
    in >> totalWorkshops >> workingWorkshops;
    in.ignore();

    if (id >= nextId) {
        nextId = id + 1;
    }
}