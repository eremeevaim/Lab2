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
    name = "����";
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
    os << "����� ID: " << p.id << endl;
    os << "��������: " << p.name << endl;
    os << "�����: " << p.length << " �" << endl;
    os << "�������: " << p.diameter << " ��" << endl;
    os << "� �������: " << (p.inRepair ? "��" : "���") << endl;
    return os;
}

istream& operator>>(istream& is, pipe& p) {
    cout << "������� �������� �����: ";
    getline(is, p.name);
    cout << "������� �����: ";
    is >> p.length;
    cout << "������� �������: ";
    is >> p.diameter;
    cout << "� ������� (1-��, 0-���): ";
    is >> p.inRepair;
    is.ignore();
    return is;
}