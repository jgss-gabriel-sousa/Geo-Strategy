#include "Engine/Components.h"

void Movement(Entity* entity,string argument){
    string keys ;
    float movSpeed;

    auto leftKey = sf::Keyboard::A;
    auto rightKey = sf::Keyboard::A;
    auto upKey = sf::Keyboard::A;
    auto downKey = sf::Keyboard::A;

    //rightKey,upKey,downKey;

    try{
        keys = argument.substr(0,argument.find("|"));
        movSpeed = stod(argument.substr(argument.find("|")+1));
    }
    catch(std::exception& e){
        Log::Push("exception in \"Movement Component\" argument");
        movSpeed = 0;
        keys = "";
    }

    if(keys == "arrows"){
        leftKey = sf::Keyboard::Left;
        rightKey = sf::Keyboard::Right;
        upKey = sf::Keyboard::Up;
        downKey = sf::Keyboard::Down;
    }

    if(sf::Keyboard::isKeyPressed(leftKey)){
        entity->SetVelocity(entity->GetVelocity().x-movSpeed,entity->GetVelocity().y);
    }
    if(sf::Keyboard::isKeyPressed(rightKey)){
        entity->SetVelocity(entity->GetVelocity().x+movSpeed,entity->GetVelocity().y);
    }
    if(sf::Keyboard::isKeyPressed(upKey)){
        entity->SetVelocity(entity->GetVelocity().x,entity->GetVelocity().y-movSpeed);
    }
    if(sf::Keyboard::isKeyPressed(downKey)){
        entity->SetVelocity(entity->GetVelocity().x,entity->GetVelocity().y+movSpeed);
    }
}
