#include "CountryState.h"

CountryState::CountryState(string baseName,string n,double popTotal, vector<City*> gCities,double a,sf::Vector2f position,
                           AssetManager* as,vector<pair<string,unsigned int>> nr,vector<Industry> i){
    name = n;
    population = popTotal;
    tag = baseName;
    naturalResources = nr;
    industries = i;
    a = area;
    Init(position,as);
}

void CountryState::Init(sf::Vector2f position,AssetManager* as){
    asset = as;

    greatCitiesPop = 0;
    /*
    for(int i = 0; i<gCities.size(); i++){
        greatCitiesPop += gCities[i]->population;
        greatCities.push_back(gCities[i]);
    }*/

//    otherPop = popTotal-greatCitiesPop;

    spriteColor = sf::Color(100,0,0,255);
    sprite.setTexture(as->GetTexture(tag));
    sprite.setPosition(position);

    text.setOutlineThickness(10);
    text.setOutlineColor(sf::Color::Black);
    text.setString(name);
    text.setCharacterSize(50);
    text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/3);
    text.setPosition(sprite.getPosition().x+sprite.getGlobalBounds().width/2,
                     sprite.getPosition().y+sprite.getGlobalBounds().height/2);
}
