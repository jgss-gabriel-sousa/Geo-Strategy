#include "Engine/Components.h"
#include "Engine/InputManager.h"
#include <SFML/Graphics.hpp>

void Draggable(Entity* entity, string argument,sf::RenderWindow& window, sf::View worldView){
    static bool clicked;
    static string id;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clicked == false){
        if(entity->sprite.getGlobalBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window),worldView)))){
            clicked = true;
            id = entity->GetId();
        }
    }

    if(clicked == true && entity->GetId() == id){
        entity->sprite.setPosition(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window),worldView)));
        entity->SetVelocity(0,0);

        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            clicked = false;
        }
    }
}
