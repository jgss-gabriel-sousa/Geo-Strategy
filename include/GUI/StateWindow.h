#pragma once

#include "UI.h"
#include "Engine/AssetManager.h"
#include "GUI/GUIManager.h"

namespace UI{
    class StateWindow : public BaseEntity{
    public:
        StateWindow(AssetManager*,sf::Vector2f,sf::Vector2f,sf::RenderWindow*);
        StateWindow(){};
        ~StateWindow(){};

        void Update(sf::RenderWindow*,sf::View);
        void Draw(sf::RenderWindow*);
        void Set(string);
        string Return(string);

    private:
        bool visible = true;

        AssetManager* asset;
        GUIManager gui;

        sf::Vector2f position,Size;
    };
}
