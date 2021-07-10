#pragma once

#include "Database.h"
#include <algorithm>

class Simulation{
public:
    Simulation(Database*);
    virtual ~Simulation(){};

    void Init();
    void Update(); //Everyday update the player country, others countries update 20 a day
    void CountrySimulation(Country*);

    Database* database;
};
