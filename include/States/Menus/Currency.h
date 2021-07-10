#pragma once

#include <SFML/Graphics.hpp>
#include "Engine/State.h"
#include "Engine/Engine.h"
#include "Country.h"
#include "States/GameMenu/GUI.h"

class CurrencyMenu : public State{
public:
    CurrencyMenu(GameDataRef data,Country*,GUIManager*);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

private:
    GameDataRef data;
    GUIManager gui;
    GUIManager* baseGui;
    Database* database = &data->database;

    Country* playerCountry;

    sf::Clock inputDelay;

    const short int sepValue = 20;
    unsigned int separator = 20;

    sf::RectangleShape window;
    sf::RectangleShape closeButton;
    sf::Text text;

    float newInterestRate;
};
