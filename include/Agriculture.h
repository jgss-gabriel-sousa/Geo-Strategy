#pragma once

#include <string>
#include <vector>
#include "Market.h"
#include "JobMarket.h"
#include "Country.h"

class Country;

class Agriculture{
public:
    Agriculture(){};
    virtual ~Agriculture(){};

    void Update(Market*,JobMarket*,Country*,int);
    void YearUpdate();
    void Build(Market*,double,double);
    void Dismantle(Market*,JobMarket*);
    void Hire(JobMarket*);

    string tag;
    string name;
    string category;
    double qty = 0;

    double value = 0;
    double cash = 1;
    double balance = 0;
    double yearProfit = 0;
    double employess = 0;
    double maxEmployess = 0;

    vector<pair<string,int>> buildNeeds;
    pair<string,int> output;
    unsigned int baseGeneralJobs=0;
    double generalJobs=0;
    unsigned int baseTechnicalJobs=0;
    double technicalJobs=0;
    unsigned int baseExpertJobs=0;
    double expertJobs=0;

    float efficiency = 1; //Upgraded with Technology
    float productionEfficiency = 1; //Reduce with lack of production resources

    float baseEletricityNeeds=0;
    float baseWaterNeeds=0;
    float eletricityNeeds=0;
    float waterNeeds=0;
};
