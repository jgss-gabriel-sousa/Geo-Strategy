#pragma once

#include "UI.h"
#include "GUI/Text.h"

namespace UI{
    class TextList : public BaseEntity{
    public:
        TextList(vector<string>strings,int Size,sf::Vector2f firstPosition,int spacing,string font,string alignment,
                 string style,AssetManager* assetM);
        ~TextList(){};


        void Update(sf::RenderWindow*,sf::View);
        void Draw(sf::RenderWindow*);
        void Set(string);
        string Return(string);

    private:
        bool visible = true;

        vector<UI::Text> texts;
    };
}
