#pragma once

#include <string>

using namespace std;

class Party{
public:
    Party(){};
    virtual ~Party(){};

    string name;
    string ideology;
    double cash;
    float popularity;
};
