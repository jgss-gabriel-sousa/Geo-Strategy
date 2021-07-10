#include "City.h"

City::City(string n,string t,double pop,sf::Vector2f pos){
    name = n;
    type = t;
    population = pop;

    if((population/1000000)*2 < 30){
        sprite.setRadius((population/1000000)*2);
    }else{
        sprite.setRadius(30);
    }
    sprite.setOrigin(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2);
    sprite.setPosition(pos);
    text.setPosition(pos);
    text.setString(name);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
}
