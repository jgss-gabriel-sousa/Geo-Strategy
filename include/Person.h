#pragma once

#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "Engine/AssetManager.h"

using namespace std;

struct PersonSprite{
    sf::Vector2f position;
    sf::Sprite face;
    sf::Sprite body;
    sf::Sprite eyes;
    sf::Sprite hair;
};

class Person{
public:
    Person(){};
    virtual ~Person(){};

    void GenRandom(string,AssetManager*);

    const int BODY_QTY = 4;
    const int EYES_QTY = 4;
    const int FACE_QTY = 4;
    const int HAIR_QTY = 4;

    PersonSprite sprite;
    short int popularity;
    string ideology;
    string sex;
    string gender;
    string description;
};
