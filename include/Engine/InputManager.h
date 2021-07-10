#pragma once

#include <SFML/Graphics.hpp>

class InputManager{
public:
    InputManager(){}
    ~InputManager(){}

    bool IsSpriteClicked(sf::FloatRect objectBounds, sf::Mouse::Button button, sf::RenderWindow &window, sf::View view);
    bool IsOverSprite(sf::FloatRect objectBounds, sf::RenderWindow &window, sf::View view);
    bool BoxCollision(sf::FloatRect object1Bounds, sf::FloatRect object2Bounds);
    sf::Vector2f GetMousePosition(sf::RenderWindow &window, sf::View view);
};
