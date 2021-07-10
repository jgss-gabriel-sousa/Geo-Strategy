#pragma once

#include "UI.h"
#include "GUI/Button.h"

namespace UI{
    class ButtonBar : public BaseEntity{
    public:
        ButtonBar(vector<string>buttonTexts,string,sf::Vector2f Size,sf::Vector2f firstPosition,int spacing,sf::Font& font,AssetManager*);
        ~ButtonBar(){};


        void Update(sf::RenderWindow*,sf::View);
        void Draw(sf::RenderWindow*);
        void Set(string);
        string Return(string);
        void UpdateStyle();


    private:
        bool visible = true;

        vector<UI::Button> buttons;
    };
}
