#pragma once

#include "Person.h"

class PoliticalParty{
public:
    PoliticalParty();
    virtual ~PoliticalParty();

    vector<Person> politics;
};
