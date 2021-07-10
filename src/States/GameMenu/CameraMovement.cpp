#include "States/GameMenu.h"

void GameMenu::CameraInit(){
    camera.setPosition(playerCountry->data.capitalState->sprite.getPosition().x+
                            playerCountry->data.capitalState->sprite.getGlobalBounds().width/2,
                       playerCountry->data.capitalState->sprite.getPosition().y+
                            playerCountry->data.capitalState->sprite.getGlobalBounds().height/2);
}

void GameMenu::CameraMovement(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) && inputDelay.getElapsedTime().asSeconds() > 1){
        data->gui.Set("playerFace","visible=false");
        inputDelay.restart();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add) && inputDelay.getElapsedTime().asSeconds() > 1){
        data->gui.Set("playerFace","visible=true");
        inputDelay.restart();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        camera.setPosition(camera.getPosition().x-(data->engine.worldView.getSize().x/100),camera.getPosition().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        camera.setPosition(camera.getPosition().x+(data->engine.worldView.getSize().x/100),camera.getPosition().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        camera.setPosition(camera.getPosition().x,camera.getPosition().y-(data->engine.worldView.getSize().x/100));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        camera.setPosition(camera.getPosition().x,camera.getPosition().y+(data->engine.worldView.getSize().x/100));
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        sf::Vector2f mousePos = sf::Vector2f(data->input.GetMousePosition(data->window,data->window.getDefaultView()));
        int movSpeed = data->engine.worldView.getSize().x/100;

        if(movSpeed < 1)
            movSpeed = 1;

        if(mousePos.x < data->engine.screenWidth/4){
            camera.setPosition(camera.getPosition().x-movSpeed,camera.getPosition().y);
        }
        else if(mousePos.x > data->engine.screenWidth-(data->engine.screenWidth/4)){
            camera.setPosition(camera.getPosition().x+movSpeed,camera.getPosition().y);
        }
        if(mousePos.y < data->engine.screenHeight/4){
            camera.setPosition(camera.getPosition().x,camera.getPosition().y-movSpeed);
        }
        else if(mousePos.y > data->engine.screenHeight-(data->engine.screenHeight/4)){
            camera.setPosition(camera.getPosition().x,camera.getPosition().y+movSpeed);
        }
    }

    if(camera.getPosition().x < 0){
        camera.setPosition(worldMap.backgroundW.getGlobalBounds().width*2,camera.getPosition().y);
    }
    if(camera.getPosition().x > worldMap.backgroundE.getGlobalBounds().width*2){
        camera.setPosition(0,camera.getPosition().y);
    }
    if(camera.getPosition().y < 0){
        camera.setPosition(camera.getPosition().x,0);
    }
    if(camera.getPosition().y > worldMap.backgroundW.getGlobalBounds().height){
        camera.setPosition(camera.getPosition().x,worldMap.backgroundW.getGlobalBounds().height);
    }


    data->engine.worldView.setCenter(camera.getPosition());
}

void GameMenu::MoveCameraTo(int x, int y){
    camera.setPosition(x,y);
}
