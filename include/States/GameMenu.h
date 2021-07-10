#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Engine/State.h"
#include "Engine/Engine.h"
#include "WorldMap.h"
#include "MilitaryView.h"
#include "Country.h"
#include "Simulation.h"
#include "Event.h"

//Sub-Menus
#include "States/Menus/Finances.h"
#include "States/Menus/Currency.h"
#include "States/Menus/Industry.h"
#include "States/Menus/Services.h"
#include "States/Menus/Agriculture.h"
#include "States/Menus/State Budget.h"
#include "States/Menus/Civil Servant.h"


class GameMenu : public State{
public:
    GameMenu(GameDataRef data);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

    void CameraMovement();
    void CameraInit();
    void MoveCameraTo(int x, int y);
    void Song();

    void InitGUI();
    void UpdateGUI();

    void Resume() override;

private:
    GameDataRef data;

    sf::Clock inputDelay;
    sf::Clock simulationTick;
    sf::Clock songClock;
    sf::Clock uiClock;
    float gameVelocity = 0;
    short int speedOption = 0;

    short int songsDelay;
    bool inDelay;
    int lastSong = -1;
    sf::Sound songs;

    GUIManager* gui = &data->gui;
    Country* playerCountry;
    CountryState* stateClicked;
    string stateName;

    WorldMap worldMap = WorldMap(&data->assets,&data->database);
    MilitaryView military = MilitaryView(&data->assets,&data->database,&data->engine);
    Simulation simulation = Simulation(&data->database);

    sf::Sprite camera;

    string countryName="AF";
    string leaderName="Lulonaro";

    Event event;
};
