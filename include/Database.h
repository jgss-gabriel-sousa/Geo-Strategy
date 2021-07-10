#pragma once

#include <Country.h>
#include <Currency.h>
#include <Industry.h>
#include <Agriculture.h>
#include <PoliticalParty.h>
#include <map>

struct Resource{
    string name;
    double production;
    double maxProduction;
};

struct Date{
    int year;
    int month;
    int day;
    double total;
};

class Database{
public:
    Database();
    virtual ~Database(){};

    void AdvanceTime();
    string GetDate(string);
    string GetDay(){return to_string(gameDate.day);}

    float CurrencyExchange(string,string);
    string ValueToScale(double,string,int);
    string ValueToPercentage(double,int);
    string SetPrecision(double,int);


    Date gameDate;

    //Economy
    Market globalMarket;
    map<string,Industry> industry;
    map<string,Agriculture> agriculture;
    map<string,Services> services;
    map<string,Resource> naturalResources;

    //Others
    map<string,PoliticalParty> parties;
    map<string,Person> personalities;
    //map<string,Disaster> disasters;
    //map<string,TerroristGroup>terroristGroups;

    //Military
    //map<string,Army> militaryUnits;

    //Countries
    map<string,Country> countries;
    vector<pair<double,string>> countryRanking;
    map<string,CountryState> states;
    map<string,City> cities;
    map<string,Currency> currencies;
    //map<string,vector<InterOrgs>> internacionalOrgs;
};
