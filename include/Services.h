#pragma once

#include <string>
#include <vector>
#include "Market.h"
#include "JobMarket.h"
#include "Country.h"

class Country;

class Services{
public:
    Services(){};
    virtual ~Services(){};

    void Update(Market*,JobMarket*,Country*);
    void YearUpdate();
    void Build(Market*);
    void Dismantle(Market*,JobMarket*);
    void Hire(JobMarket*);
    double Request(double);

    string tag;
    string name;
    string category;
    double qty = 0;

    double value=0;
    double cash = 1;
    double demand=0;
    double cost=0;
    double price=1;
    double balance=0;
    double yearProfit=0;
    double employess = 0;
    double maxEmployess = 0;

    vector<pair<string,double>> buildNeeds;
    vector<pair<string,double>> input;
    pair<string,double> output;
    unsigned int baseGeneralJobs=0;
    double generalJobs=0;
    unsigned int baseTechnicalJobs=0;
    double technicalJobs=0;
    unsigned int baseExpertJobs=0;
    double expertJobs=0;

    float efficiency = 1; //Upgraded with Technology
    float productionEfficiency = 1; //Reduce with lack of production resources

    float baseEletricityNeeds = 0;
    float baseWaterNeeds=0;
    float eletricityNeeds=0;
    float waterNeeds=0;
};
