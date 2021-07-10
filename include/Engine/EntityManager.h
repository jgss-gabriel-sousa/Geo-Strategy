#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.h"

#include "Components.h"

class EntityManager{
    public:
        EntityManager();
        ~EntityManager(){};

        void AddEntity(Entity* entity);
        void Update(sf::RenderWindow &window,sf::View);

        std::vector<Entity*> entities;
};
