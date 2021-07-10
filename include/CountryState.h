#pragma once

#include <vector>
#include <string>
#include "City.h"
#include "Industry.h"
#include "Agriculture.h"
#include "Services.h"
#include "Engine/AssetManager.h"
#include "Engine/Log.h"
#include "SFML/Graphics.hpp"

class Agriculture;
class Industry;
class Services;


using namespace std;

class CountryState{
public:
    CountryState(){}
    CountryState(string,string,double,vector<City*>,double,sf::Vector2f,AssetManager*,vector<pair<string,unsigned int>>,
                 vector<Industry>);
    virtual ~CountryState(){};

    static sf::Vector2f GetStateShape(sf::Color,int,string,AssetManager*);
    void SetProvinceColor(sf::Color);
    void Init(sf::Vector2f,AssetManager*);


    AssetManager* asset;
    sf::Sprite sprite;
    sf::Color spriteColor;
    sf::Text text;

    vector<City*> greatCities;
    double greatCitiesPop;
    double otherPop;

    vector<Industry> industries;
    vector<Agriculture> agriculture;
    vector<Services> services;

    vector<pair<string,unsigned int>> naturalResources;

    string tag;
    string name;
    string terrain;
    vector<string> claim;
    vector<string> core;

    double population;

    double childrens;
    double young;
    double adult;
    double old;

    double death;
    double birth;
    double migration;

    double area;
};
