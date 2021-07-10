#pragma once

//#include "Population.h"
#include "SFML/Graphics.hpp"
#include <string>

using namespace std;

class City{
public:
    City(){}
    City(string,string,double,sf::Vector2f);
    virtual ~City(){};

    string name;
    string type;
    double population;
    sf::CircleShape sprite;
    sf::Text text;
};
