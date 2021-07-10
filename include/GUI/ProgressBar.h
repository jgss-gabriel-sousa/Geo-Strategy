#pragma once

#include "UI.h"
#include "Engine/AssetManager.h"

namespace UI{
    class ProgressBar : public BaseEntity{
        #define BAR_FONT "arial"

        public:
            ProgressBar(float value,float maxValue,sf::Vector2f pos,sf::Vector2f Size,string caption,string style,int,sf::Font&,AssetManager*);
            ~ProgressBar(){};

            void Update(sf::RenderWindow*,sf::View);
            void Draw(sf::RenderWindow*);
            void Set(string);
            string Return(string);
            void UpdateStyle();

        private:
            bool visible = true;

            int thickness;

            string style;

            AssetManager* asset;

            sf::RectangleShape bar;
            sf::RectangleShape barBackground;
            sf::Text caption;

            float value;
            float maxValue;
            float barWidth;
    };
}
