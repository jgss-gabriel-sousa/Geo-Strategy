#pragma once

#include "UI.h"
#include "Engine/DEFINITIONS.h"

namespace UI{
    class Slider : public BaseEntity{
        #define SLIDER_FONT "arial"

        public:
            Slider(float,float,float,sf::Vector2f,sf::Vector2f,string,string,int,sf::Font&);
            ~Slider(){};

            void Update(sf::RenderWindow*,sf::View);
            void Draw(sf::RenderWindow*);
            void Set(string);
            string Return(string);
            void UpdateStyle();

        private:
            bool visible = true;
            bool first = true;
            bool clicked = false;

            string style;

            sf::RectangleShape bar;
            sf::RectangleShape slider;
            float maxBarValue;
            float minBarValue;
            sf::Text caption;
            sf::Text max_value;
            sf::Text min_value;

            sf::Clock internalClock;

            float value;
            float maxValue;
            float minValue;
            float barWidth;
    };
}
