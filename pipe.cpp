#include "pipe.h"
#include <string>
using namespace std;

int pipe::next_id = 1;

pipe::pipe(string n, int l, int d, bool rep)
{
    setlocale(LC_ALL, "RU");
    id = next_id++;
    name = n;
    length = l;
    diameter = d;
    inRepair = rep;
}

pipe::pipe()
{
    id = next_id++;
    name = "Тест";
    length = 10;
    diameter = 20;
    inRepair = true;
}

int pipe::GetId() const {
    return id;
}

string pipe::GetName() const {
    return name;
}

int pipe::GetLength() const {
    return length;
}

int pipe::GetDiameter() const {
    return diameter;
}

bool pipe::GetInRepair() const {
    return inRepair;
}

void pipe::SetInRepair(bool s) {
    inRepair = s;
}

void pipe::SetName(string st) {
    name = st;
}

void pipe::SetLength(int l) {
    length = l;
}

void pipe::SetDiameter(int d) {
    diameter = d;
}

ostream& operator<<(ostream& os, const pipe& p) {
    os << "Труба ID: " << p.id << endl;
    os << "Название: " << p.name << endl;
    os << "Длина: " << p.length << " м" << endl;
    os << "Диаметр: " << p.diameter << " мм" << endl;
    os << "В ремонте: " << (p.inRepair ? "Да" : "Нет") << endl;
    return os;
}

istream& operator>>(istream& is, pipe& p) {
    cout << "Введите название трубы: ";
    getline(is, p.name);
    cout << "Введите длину: ";
    is >> p.length;
    cout << "Введите диаметр: ";
    is >> p.diameter;
    cout << "В ремонте (1-да, 0-нет): ";
    is >> p.inRepair;
    is.ignore();
    return is;
}