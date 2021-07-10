#pragma once

#include "UI.h"
#include "Engine/AssetManager.h"

namespace UI{
    class Text : public BaseEntity{
    public:
        Text(AssetManager*,sf::Vector2f,string,string,unsigned int,string);
        ~Text(){};

        void Update(sf::RenderWindow*,sf::View);
        void Draw(sf::RenderWindow*);
        void Set(string);
        string Return(string);

    private:
        bool visible = true;
        bool visibilityChange = false;

        string textAlignment;
        string style;
        double value;
        double turningPointValue;

        AssetManager* assets;
        sf::Text text;

        sf::Vector2f textPos;
    };
}
