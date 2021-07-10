#pragma once

#include <SFML/Graphics.hpp>
#include "../../../src/SelbaWard/PieChart.hpp"
#include "Engine/State.h"
#include "Engine/Engine.h"
#include "Country.h"
#include "States/GameMenu/GUI.h"

class ServicesMenu : public State{
public:
    ServicesMenu(GameDataRef data,Country*,GUIManager*);

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
    sw::PieChart pieChart;
};
