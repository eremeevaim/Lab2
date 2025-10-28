#pragma once
#include <string>
#include <iostream>

class pipe {
private:
    int id;
    std::string name;
    int length;
    int diameter;
    bool inRepair;
    static int next_id;

public:
    pipe(std::string n, int l, int d, bool rep);
    pipe();

    int GetId() const;
    std::string GetName() const;
    int GetLength() const;
    int GetDiameter() const;
    bool GetInRepair() const;

    void SetInRepair(bool s);
    void SetName(std::string st);
    void SetLength(int l);
    void SetDiameter(int d);

    friend std::ostream& operator<<(std::ostream& os, const pipe& p);
    friend std::istream& operator>>(std::istream& is, pipe& p);
};