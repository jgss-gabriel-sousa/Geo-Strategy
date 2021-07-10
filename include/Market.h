#pragma once

#include <string>
#include <map>
#include "Product.h"
#include "Engine/Log.h"

class Market{
public:
    Market(){};
    virtual ~Market(){};

    pair<double,double> Buy(string, double);
    double Sell(string, double);
    void Update();
    void YearUpdate();
    void SetPrice(string,double);
    double GetPrice(string);

    double imports = 0;
    double exports = 0;
    Market* globalMarket;
    string hierarchy = "global";

    map<string,Product> market;
};
