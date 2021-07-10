#pragma once

#include "GUI/Button.h"
#include "GUI/Text.h"
#include "GUI/ProgressBar.h"
#include "GUI/ButtonBar.h"
#include "GUI/Slider.h"
#include "GUI/TextList.h"
#include "stdlib.h"

#include "Engine/AssetManager.h"

#include <map>

using namespace std;

class GUIManager{
public:
    enum Style{
        light,
        dark
    };

    GUIManager(){};
    ~GUIManager(){};

    void Init(AssetManager* asset, sf::RenderWindow* window);
    void Update();
    void Draw();
    string Get(string,string);
    void Set(string name,string argument);
    void Reset();
    void Remove(string name);

    void AddButton(string,sf::Vector2f,sf::Vector2f,string,string);
    void AddText(string,sf::Vector2f,string,string,unsigned int,string);
    void AddProgressBar(string,float,float,sf::Vector2f,sf::Vector2f,string,string,int);
    void AddButtonBar(string,vector<string>,string,sf::Vector2f,sf::Vector2f,int);
    void AddSlider(string,float,float,float,sf::Vector2f,sf::Vector2f,string,string,int);
    void AddTextList(string,vector<string>strings,int Size,sf::Vector2f firstPosition,int spacing,string font,string alignment,
                     string style);

    //void AddTextField(string name,sf::Vector2f position);
    //void AddListBox(string name,sf::Vector2f position);
    //void AddCheckBox(string name,sf::Vector2f position);

private:
    map<string,UI::BaseEntity*> elements;

    AssetManager* asset;
    sf::RenderWindow* window;
};
