#include "States/GameMenu.h"

GameMenu::GameMenu(GameDataRef data) : data(data){
    ;
}

void GameMenu::Resume(){
    //InitGUI();
}

void GameMenu::Init(){
    data->engine.playerCountry = countryName;
    playerCountry = &data->database.countries[data->engine.playerCountry];
    stateName = playerCountry->data.capitalState->name;

    data->engine.worldView.setSize(data->engine.screenWidth,data->engine.screenHeight);

    InitGUI();
    worldMap.Init();
    military.Init();
    simulation.Init();
    CameraInit();

    //event.Init({"ola","teste"},{400,300},&data->window,&data->assets);
}

void GameMenu::HandleInput(){
    CameraMovement();
}

void GameMenu::Update(float dt){
    if(simulationTick.getElapsedTime().asSeconds() >= gameVelocity && gameVelocity != 0){
        simulation.Update();
        data->database.AdvanceTime();
        simulationTick.restart();
    }

    Song();

    if(uiClock.getElapsedTime().asSeconds() > 0.1){
        UpdateGUI();
    }
}

void GameMenu::Song(){
    if(data->assets.songs.getStatus() != sf::Sound::Playing && !inDelay){
        inDelay = true;
        songClock.restart();
        songsDelay = rand()%20+10;
    }
    else if(inDelay && songClock.getElapsedTime().asSeconds() > songsDelay){
        inDelay = false;

        int song;
        do{
            song = rand()%10;
        }while(song == lastSong);
        lastSong = song;

        data->assets.songs.setBuffer(data->assets.GetAudio("song ("+to_string(song)+")"));
        data->assets.songs.play();
        Log::Push("Song: "+to_string(song));
    }
}

void GameMenu::Draw(float dt){
    worldMap.Draw(&data->window,&data->engine.worldView,&data->engine.GUIview,&data->input,&stateName);
    stateClicked = &data->database.states[stateName];

    military.Draw(&data->window,&data->engine.worldView,&data->engine.GUIview,&data->input);

    //event.Draw(&data->window,&data->engine.GUIview);
}







