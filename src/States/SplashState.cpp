#include "States/SplashState.h"
#include "States/Loading.h"

SplashState::SplashState(GameDataRef data) : data(data){
    ;
}

void SplashState::Init(){
    ;
}

void SplashState::HandleInput(){
    ;
}

void SplashState::Update(float dt){
    if(stateClock.getElapsedTime().asSeconds() > 0){
        data->machine.AddState(StateRef(new Loading(this->data)),true);
    }
}

void SplashState::Draw(float dt){
    ;
}







