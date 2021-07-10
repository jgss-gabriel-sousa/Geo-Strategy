#include "Engine/Components.h"

void Rotate(Entity* entity,string argument){
    string keys;
    string typeOfMovement;
    float rotateSpeed;

    auto leftKey = sf::Keyboard::A;
    auto rightKey = sf::Keyboard::A;
    auto upKey = sf::Keyboard::A;
    auto downKey = sf::Keyboard::A;

    try{
        keys = argument.substr(0,argument.find("|"));
        argument = argument.substr(argument.find("|")+1);
        typeOfMovement = argument.substr(0,argument.find("|"));
        if(typeOfMovement != "abruptly")
            rotateSpeed = stod(argument.substr(argument.find("|")+1));
    }
    catch(std::exception& e){
        Log::Push("exception in \"rotate\" argument");
        rotateSpeed = 0;
        typeOfMovement = "";
        keys = "";
    }

    if(keys == "arrows"){
        leftKey = sf::Keyboard::Left;
        rightKey = sf::Keyboard::Right;
        upKey = sf::Keyboard::Up;
        downKey = sf::Keyboard::Down;
    }
    else if(keys == "wasd"){
        leftKey = sf::Keyboard::A;
        rightKey = sf::Keyboard::D;
        upKey = sf::Keyboard::W;
        downKey = sf::Keyboard::S;
    }

    if(sf::Keyboard::isKeyPressed(leftKey)){
        if(typeOfMovement == "gradually"){
            if(entity->sprite.getRotation() > 270+rotateSpeed || entity->sprite.getRotation() > 270-rotateSpeed){
                if(1){
                    ;
                }
            }
            //entity->sprite.setRotation(entity->sprite.getRotation() - rotateSpeed);
        }
        else if(typeOfMovement == "abruptly"){
            entity->sprite.setRotation(270);
        }
    }
    if(sf::Keyboard::isKeyPressed(rightKey)){
        if(typeOfMovement == "gradually"){
            ;
        }
        else if(typeOfMovement == "abruptly"){
            entity->sprite.setRotation(90);
        }
    }
    if(sf::Keyboard::isKeyPressed(upKey)){
        if(typeOfMovement == "gradually"){
            ;
        }
        else if(typeOfMovement == "abruptly"){
            entity->sprite.setRotation(180);
        }
    }
    if(sf::Keyboard::isKeyPressed(downKey)){
        if(typeOfMovement == "gradually"){
            ;
        }
        else if(typeOfMovement == "abruptly"){
            entity->sprite.setRotation(0);
        }
    }
}
