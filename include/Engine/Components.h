#pragma once

#include <iostream>
#include <math.h>
#include "Entity.h"

using namespace std;

//Physics
extern void Gravity(Entity*,string);
extern void Bullet(Entity*,string);
extern void Wrap(Entity*,string,sf::RenderWindow&,sf::View);
extern void Solid(Entity*,string,vector<Entity*>);

//Gameplay
extern void Movement(Entity*,string);
extern void Rotate(Entity*,string);
extern void SnapToGrid(Entity*,string);

//UI
extern void Draggable(Entity*,string,sf::RenderWindow&,sf::View);
extern void Debug(Entity*,string);
