#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "log.h"

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "GUI/GUIManager.h"
#include "DEFINITIONS.h"
#include "Database.h"

struct EngineInfo{
    int screenWidth;
    int screenHeight;
    int fps;
    string language;
    sf::Color backgroundColor;
    sf::Event event;
    sf::View GUIview;
    sf::View worldView;
    string playerCountry;
    string dataFormat;
    float gameVelocity;
};

struct GameData{
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
    EntityManager entities;
    GUIManager gui;
    EngineInfo engine;
    Database database;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Engine{
public:
    Engine();

    sf::Vector2f actualResolution;
    const int framerate = 60;
    const string title = "Strategy";

private:
    const float dt = 1.0f/60.0f;
    sf::Clock gameClock;

    sf::Event event;

    GameDataRef data = std::make_shared<GameData>();

    void UserConfigs();
    void CheckFocus();
    void UpdateAndDrawEntities();
    void UpdateUI();
    void CorrectUIScale(const sf::View);
    void DrawUI();
    void GlobalWindowEvents();
    void UpdateEngineInfo(float);

    void Run();
};






