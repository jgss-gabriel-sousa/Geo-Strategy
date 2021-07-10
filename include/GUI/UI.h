#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Engine/Log.h"
#include "Engine/Colors.h"

using namespace std;

namespace UI{
    class BaseEntity{
        public:
            virtual void Update(sf::RenderWindow*,sf::View) = 0;
            virtual void Draw(sf::RenderWindow*) = 0;
            virtual void Set(string) = 0;
            virtual string Return(string) = 0;
    };
}
