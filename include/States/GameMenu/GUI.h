#pragma once

#include "SFML/Graphics.hpp"
#include "Engine/Engine.h"

extern void SubMenusInit(GUIManager*,GUIManager*,AssetManager*, sf::RenderWindow*,sf::Text*,sf::RectangleShape*,sf::RectangleShape*);
extern void SubMenusUpdate(GUIManager*,StateMachine*,InputManager*,sf::RenderWindow*,sf::View*,sf::RectangleShape*,sf::RectangleShape*);
