#pragma once

#include <SFML/Graphics.hpp>
#include "Engine/State.h"
#include "Engine/Engine.h"
#include "Engine/Entity.h"

class SplashState : public State{
public:
    SplashState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

private:
    GameDataRef data;
    Entity entity = Entity("box",sf::Vector2f(START_SCREEN_WIDTH*0.7,START_SCREEN_HEIGHT*0.5));
    Entity entity2 = Entity("box2",sf::Vector2f(START_SCREEN_WIDTH*0.7,START_SCREEN_HEIGHT*0.7));

    sf::Clock stateClock;
};
