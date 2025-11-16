#include "pipe.h"
#include "utils.h"

int Pipe::nextId = 1;

Pipe::Pipe() : id(nextId++), name("Труба"), length(100.0), diameter(500), inRepair(false) {}

Pipe::Pipe(const std::string& name, double length, int diameter, bool inRepair)
    : id(nextId++), name(name), length(length), diameter(diameter), inRepair(inRepair) {
}

void Pipe::readFromConsole() {
    std::cout << "Добавление трубы (ID: " << id << ")\n";

    std::cout << "Название: ";
    name = getStringInput();

    std::cout << "Длина (км): ";
    length = getPositiveDouble();

    std::cout << "Диаметр (мм): ";
    diameter = getPositiveInt();

    std::cout << "В ремонте? (1-да, 0-нет): ";
    inRepair = getYesNoInput();
}

void Pipe::printToConsole() const {
    std::cout << "=== Труба ID: " << id << " ===\n";
    std::cout << "Название: " << name << "\n";
    std::cout << "Длина: " << length << " км\n";
    std::cout << "Диаметр: " << diameter << " мм\n";
    std::cout << "В ремонте: " << (inRepair ? "Да" : "Нет") << "\n\n";
}

void Pipe::saveToFile(std::ostream& out) const {
    out << id << "\n" << name << "\n" << length << "\n" << diameter << "\n" << inRepair << "\n";
}

void Pipe::loadFromFile(std::istream& in) {
    in >> id;
    in.ignore();
    std::getline(in, name);
    in >> length >> diameter >> inRepair;
    in.ignore();

    // Обновляем nextId чтобы избежать дублирования ID
    if (id >= nextId) {
        nextId = id + 1;
    }
}