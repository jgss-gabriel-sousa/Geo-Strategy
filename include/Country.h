#pragma once

#include <vector>
#include <string>
#include "CountryState.h"
#include "Currency.h"
#include "SFML/Graphics.hpp"

class CountryState;

using namespace std;

struct Units{
    string name;
    string type;
    float range;
    float velocity;
    string attackType;
    float precision;
    float damage;
    float resistance;
    float maintenance;
    float maintenanceCosts;

    sf::Sprite sprite;
    sf::RectangleShape selection;
    sf::Sprite icon;

    bool selected;
    sf::Vector2f posToMove;
};

struct CountryDataPackage{
    //Geography
    string name;
    string tag;
    double area;
    double population;
    sf::Color countryColor;
    City* capital;
    CountryState* capitalState;


    //State
    string headerOfState;
    string governmentType;
    short int headerTerm;
    long int lastElection;
    int suffrage;
    int suffrageAge;
    int legalSystem;
    int broadcastMedia;
    vector<CountryState*> states;
    //vector<Parties*> parties;
    //vector<Culture*> culture;
    //vector<Congress*> congress;
    map<string,short int> diplomacy;
    map<string,double> subsidies;
    double score;

    //Economy
    Currency* currency;
    bool stateInterestRate;
    float interestRate;
    JobMarket jobMarket;
    Market nationalMarket;
    vector<double> stockExchangeVariation;
    double stockExchange=0;
    double exports=0;
    double imports=0;

    double gdp; //Millions
    float gdpGrowth;

    double industryGdp=0;
    double servicesGdp=0;
    double agricultureGdp=0;
    double miningGdp=0;

    double budget; //Millions
    double budgetCollection=0; //Millions
    double budgetRevenue; //Millions
    double budgetExpenditure; //Millions
    double debt;

    double stateCash=0;
    double poorClassCash=0;
    double mediumClassCash=0;
    double richClassCash=0;
    double investmentFund=0;
    double investmentFundProfit=0;
    double investors=0;
    double householdConsumption=0;

    double averagePrice;
    vector<float> inflationVariation;
    float yearInflation;
    float inflation;
    double oldAvgPrice=0;
    double countryReserves;

    float laborForce;
    double generalJobs;
    double technicalJobs;
    double expertJobs;
    float unemployment;
    float unemploymentGrowth;

    float gini;

    //People
    float idh;
    double poorClass=0;
    float poorClassMilitancy;
    double mediumClass;
    float mediumClassMilitancy;
    double richClass;
    float richClassMilitancy;


    //Taxes
    float valueAddedTax;
    float corporateTax;
    float incomeTax;
    float industryTax;
    float importTax;
    float largeFortunesTax;
    float inheritanceTax;
    float vehicleRegistrationTax;
    float vehicleOwnershipTax;
    float propertyTax;
    float airlineTicketTax;
    float alcoholTax;

    //Population
    double childrens;
    double young;
    double adult;
    double old;

    double birth;
    double death;
    double migration;

    float urban;
    double lifeExpectancy;
    float water;
    double refugees;
    float poverty;

    //Health
    double healthBudget;
    double doctors;
    double hospitalBed;

    //Education
    double educationBudget;
    double literacy;

    //Eletricity
    float eletricityRate;
    double eletricityProduction;
    double eletricityConsumption;

    double fossilPowerPlant;
    double solarPowerPlant;
    double windPowerPlant;
    double hydroelectricPlant;
    double nuclearPowerPlant;
    double geotermalPowerPlant;
    double biomassPowerPlant;

    float eletricityFossil;
    float eletricityNuclear;
    float eletricityHydroeletric;
    float eletricityRenewable;

    //Infrastructure
    float internetRate;
    float mobilePhoneRate;
    double airports;
    double roads;
    double expressways;
    double railroad;
    double electrifiedRailroad;
    double ports;

    //Military
    double millitaryBudget;
    short int millitaryService;
    short int millitaryServiceAge;
    double activePersonnel;
    double reservePersonnel;
    double fighter;
    double attackHelicopter;
    double tank;
    double armoredVehicle;
    double selfPropelledArtillery;
    double artillery;
    double rocketProjector;
    double aircraftCarrier;
    double ships;
    double submarines;
    vector<Units> units;
};


class Country{
public:
    Country(){};
    Country(CountryDataPackage, Market* market);
    virtual ~Country(){};

    void Update(string);
    void IASimulation();
    void GDPPrevision(string);
    void FiscalYear();

    bool start = true;
    bool ia = true;

    vector<string> proposals;

    CountryDataPackage data;
    CountryDataPackage lastYearData;

    sf::Text text;
};
