#include "WorldMap.h"

WorldMap::WorldMap(AssetManager* a,Database* d){
    asset = a;
    database = d;

    mouseCollider.setTexture(asset->GetTexture("point"));
}

void WorldMap::Init(){
    //Background
    backgroundW.setTexture(asset->GetTexture("worldMapW"));
    backgroundE.setTexture(asset->GetTexture("worldMapE"));
    backgroundE.setPosition(backgroundW.getGlobalBounds().width,0);
    fakeRoundW.setTexture(asset->GetTexture("worldMapW"));
    fakeRoundW.setPosition(backgroundW.getGlobalBounds().width*2,0);
    fakeRoundE.setTexture(asset->GetTexture("worldMapE"));
    fakeRoundE.setPosition(0-backgroundW.getGlobalBounds().width,0);

    waterPlaces.setSize(sf::Vector2f(15000,7699));
    waterPlaces.setFillColor(sf::Color(0,0,100,255));

    //Cities
    City* city;
    for(auto& kv : database->cities){
        city = &kv.second;
        city->sprite.setTexture(&asset->GetTexture("city"),true);
        city->text.setFont(asset->GetFont("arial"));
    }

    //States
    CountryState* state;
    for(auto& kv : database->states){
        state = &kv.second;
        state->text.setFont(asset->GetFont("arial"));
    }

    //Countries
    Country* country;
    for(auto& kv : database->countries){
        country = &kv.second;
        country->text.setFont(asset->GetFont("arial"));
    }
}

void WorldMap::Draw(sf::RenderWindow* window, sf::View* worldView, sf::View* guiView, InputManager* input,string* stateName){
    window->setView(*worldView);

    window->draw(backgroundW);
    window->draw(backgroundE);
    window->draw(fakeRoundW);
    window->draw(fakeRoundE);

    for(const auto& kv : database->states){
        window->draw(kv.second.sprite);
    }

    for(const auto& kv : database->cities){
        window->draw(kv.second.sprite);
    }

    mouseCollider.setPosition(input->GetMousePosition(*window, *worldView));
    CountryState* c;
    for(auto& kv : database->states){
        c = &kv.second;

        if(c->sprite.getPosition().x+c->sprite.getGlobalBounds().width < worldView->getCenter().x-worldView->getSize().x/2)
            continue;
        else if(c->sprite.getPosition().x > worldView->getCenter().x+worldView->getSize().x/2)
            continue;
        else{
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(Collision::PixelPerfectTest(mouseCollider,kv.second.sprite,0)){
                    *stateName = c->name;
                    //clickedState = database->states[kv.first];
                    //Log::Push(clickedState->name);
                    //Log::Push(c->name);

                    //window->draw(kv.second.text);
                }
            }
        }
    }

    for(const auto& kv : database->countries){
        if(!input->IsOverSprite(kv.second.text.getGlobalBounds(),*window, *worldView))
            window->draw(kv.second.text);
    }

    for(const auto& kv : database->cities){
        window->draw(kv.second.text);
    }

    window->setView(*guiView);
}
