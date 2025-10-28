#include "cs.h"
#include <iostream>
#include <string>

int cs::next_id = 1;

cs::cs(std::string n, int num, int numw, int e)
{
    setlocale(LC_ALL, "RU");
    id = next_id++;
    name = n;
    numFac = num;
    numWorkFac = numw;
    eff = e;
}

cs::cs()
{
    id = next_id++;
    name = "����";
    numFac = 10;
    numWorkFac = 2;
    eff = 0;
}

int cs::GetId() const {
    return id;
}

std::string cs::GetName() const {
    return this->name;
}

int cs::GetNumFac() const {
    return this->numFac;
}

int cs::GetNumWorkFac() const {
    return this->numWorkFac;
}

int cs::GetEff() const {
    return this->eff;
}

double cs::GetUnusedPercentage() const {
    if (numFac == 0) return 0;
    return ((numFac - numWorkFac) * 100.0) / numFac;
}

void cs::SetName(std::string st) {
    name = st;
}

void cs::SetEff(int n) {
    eff = n;
}

void cs::SetNumFac(int n) {
    numFac = n;
}

void cs::SetNumWorkFac(int n) {
    numWorkFac = n;
}

bool cs::SetNumWorkFac(bool A) {
    if (A) {
        if ((numWorkFac + 1) > numFac) {
            return false;
        }
        else {
            numWorkFac++;
            return true;
        }
    }
    else {
        if ((numWorkFac - 1) < 0) {
            return false;
        }
        else {
            numWorkFac--;
            return true;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const cs& c) {
    os << "�� ID: " << c.id << std::endl;
    os << "��������: " << c.name << std::endl;
    os << "����� �����: " << c.numFac << std::endl;
    os << "���������� �����: " << c.numWorkFac << std::endl;
    os << "�������������: " << c.eff << "%" << std::endl;
    os << "���������������: " << c.GetUnusedPercentage() << "%" << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, cs& c) {
    std::cout << "������� �������� ��: ";
    std::getline(is, c.name);
    std::cout << "������� ����� ���������� �����: ";
    is >> c.numFac;
    std::cout << "������� ���������� ���������� �����: ";
    is >> c.numWorkFac;
    std::cout << "������� ������������� (0-100): ";
    is >> c.eff;
    is.ignore();
    return is;
}