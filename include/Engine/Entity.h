#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Log.h"
#include "AssetManager.h"

using namespace std;

class Entity{
    public:
        Entity(){};
        Entity(string id,sf::Vector2f position);
        ~Entity(){};

        void AddComponent(string component,string argument);
        void RemoveComponent(string component);
        void EditComponent(string component,string argument);

        void SetTexture(string tag,AssetManager& asset);

        void SetPosition(float x,float y);
        void SetSize(float x,float y);
        void SetVelocity(float x,float y);
        void SetColor(sf::Color);

        float GetX(){return sprite.getPosition().x;}
        float GetY(){return sprite.getPosition().y;}
        float GetWidth(){return sprite.getGlobalBounds().width;}
        float GetHeight(){return sprite.getGlobalBounds().height;}
        sf::Vector2f GetVelocity(){GetVelocityAngle();return velocity;}
        string GetId(){return id;}
        float GetDrag();
        float GetVelocityAngle();
        string GetComponentArg(string component);

        vector<pair<string,string>> components;
        sf::RectangleShape sprite;
        sf::Clock clock;

    private:
        sf::Vector2f velocity;
        int velocityAngle;
        float drag;
        string id;
};
