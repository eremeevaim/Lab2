#pragma once
#include <string>
#include <iostream>

class cs {
private:
    int id;
    std::string name;
    int numFac;
    int numWorkFac;
    int eff;
    static int next_id;

public:
    cs(std::string n, int num, int numw, int e);
    cs();

    int GetId() const;
    std::string GetName() const;
    int GetNumFac() const;
    int GetNumWorkFac() const;
    int GetEff() const;
    double GetUnusedPercentage() const;

    void SetName(std::string st);
    void SetEff(int n);
    void SetNumFac(int n);
    void SetNumWorkFac(int n);
    bool SetNumWorkFac(bool A);

    friend std::ostream& operator<<(std::ostream& os, const cs& c);
    friend std::istream& operator>>(std::istream& is, cs& c);
};