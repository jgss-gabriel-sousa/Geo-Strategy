#pragma once

#include "UI.h"
#include "Engine/AssetManager.h"

namespace UI{
    class Button : public BaseEntity{
    #define BUTTON_FONT "arial"
    #define BUTTON_AUDIO "Button Click"
    #define FRAMES_CLICK_ANIMATION 3

    public:
        Button(sf::Vector2f,sf::Vector2f,string,string,sf::Font&,AssetManager*);
        Button(){};
        ~Button(){};

        void Update(sf::RenderWindow*,sf::View);
        void Draw(sf::RenderWindow*);
        void Set(string);
        string Return(string);
        void UpdateStyle();

    private:
        bool visible = true;
        bool visibilityChange = false;
        bool clicked = false;

        string style, clickType, textAlignment = "center";

        int framesBetweenClick = FRAMES_CLICK_ANIMATION;
        int fontSize = -1;
        int addX = 0;
        int addY = 0;

        AssetManager* asset;

        sf::RectangleShape sprite;
        sf::Text text;

        sf::Vector2f spritePos;
        sf::Vector2f textPos;
    };
}
