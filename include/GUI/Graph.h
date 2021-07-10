#pragma once

#include "UI.h"
#include "Engine/AssetManager.h"

namespace UI{
    class Graph : public BaseEntity{

    public:
        Graph(sf::Vector2f,sf::Vector2f,vector<double>,vector<double>,string,string,int,sf::Font&,AssetManager*);
        Graph(){};
        ~Graph(){};

        void Update(sf::RenderWindow*,sf::View);
        void Draw(sf::RenderWindow*);
        void Set(string);
        string Return(string);
        void UpdateStyle();

    private:
        bool visible = true;
        bool visibilityChange = false;
        bool clicked = false;

        string title;
        string style;

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
