#pragma once

#include <SFML/Graphics.hpp>
#include "Engine/State.h"
#include "Engine/Engine.h"
#include "Engine/Entity.h"
#include "CountryState.h"
#include "Country.h"
#include "Currency.h"
#include "JobMarket.h"

class Loading : public State{
    #define LOADING_STAGES 10
    #define STAGES_DELAY 0.05
    #define PHRASES_COUNT 15
    #define PHRASES_COUNTDOWN 2

public:
    Loading(GameDataRef data);

    void LoadLocalisation(vector<string>);
    void LoadFlags();
    void LoadCurrencies();
    void LoadCities();
    void LoadStates();
    void LoadCountries();
    void LoadEconomy();
    void LoadSounds();
    void LoadOthers();

    void Init();

    void HandleInput(){};
    void Update(float dt);
    void Draw(float dt){};

private:
    GameDataRef data;

    int loadingStage = 0;
    bool loadingStagesNumberDebug = false;

    sf::Clock phraseClock;
    sf::Clock delayClock;
};
