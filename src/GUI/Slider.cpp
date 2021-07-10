#include "GUI/Slider.h"

UI::Slider::Slider(float minValue,float value,float maxValue,sf::Vector2f pos,sf::Vector2f Size,string captionString,string style,int borderThickness,sf::Font& font){
    this->style = style;
    this->value = value;
    this->maxValue = maxValue;
    this->minValue = minValue;

    bar.setOutlineThickness(-borderThickness);
    bar.setSize(sf::Vector2f(Size.x,Size.y/2));
    bar.setPosition(pos.x,pos.y+Size.y/2);

    slider.setSize(sf::Vector2f(Size.x*0.025,Size.y));
    if(slider.getGlobalBounds().width < 8)
        slider.setSize({8,Size.y});

    const float largura = (pos.x+Size.x)-bar.getPosition().x;
    const float poss = value/(maxValue-minValue);
    slider.setPosition(pos.x+(poss*largura),pos.y);
    slider.setOutlineThickness(-(slider.getGlobalBounds().width*0.07));
    if(slider.getOutlineThickness() < 1)
        slider.setOutlineThickness(1);
    slider.setOrigin(slider.getGlobalBounds().width/2,0);

    caption.setCharacterSize(Size.y*0.7);
    caption.setString(captionString);
    caption.setFont(font);
    caption.setOutlineThickness(caption.getCharacterSize()*0.15);

    max_value.setCharacterSize(Size.y*0.7);
    max_value.setString(to_string((int)maxValue));
    max_value.setFont(font);
    max_value.setOrigin(max_value.getGlobalBounds().width/2,max_value.getGlobalBounds().height/1.5);
    max_value.setPosition(pos.x+Size.x-max_value.getGlobalBounds().width,pos.y-slider.getGlobalBounds().height/2);
    max_value.setOutlineThickness(caption.getCharacterSize()*0.15);

    min_value.setCharacterSize(Size.y*0.7);
    min_value.setString(to_string((int)minValue));
    min_value.setFont(font);
    min_value.setOrigin(min_value.getGlobalBounds().width/2,min_value.getGlobalBounds().height/1.5);
    min_value.setPosition(pos.x+min_value.getGlobalBounds().width,pos.y-slider.getGlobalBounds().height/2);
    min_value.setOutlineThickness(caption.getCharacterSize()*0.15);
}

void UI::Slider::Update(sf::RenderWindow* window,sf::View view){
    if(visible){
        if(internalClock.getElapsedTime().asSeconds() > 0.02 || first){
            first = false;
            internalClock.restart();

            if(visible){
                UpdateStyle();
            }

            if(clicked == false && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(slider.getGlobalBounds().contains(sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window),view)))){
                    clicked = true;
                }
            }

            maxBarValue = bar.getPosition().x+bar.getGlobalBounds().width;
            minBarValue = bar.getPosition().x;

            caption.setOrigin(caption.getGlobalBounds().width/2,caption.getGlobalBounds().height/1.5);
            caption.setPosition((int)(bar.getPosition().x+(bar.getGlobalBounds().width/2)),
                                (int)(bar.getPosition().y-slider.getGlobalBounds().height));

            if(clicked == true){
                slider.setPosition(sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window),view)).x,slider.getPosition().y);


                if(slider.getPosition().x < minBarValue){
                    slider.setPosition(minBarValue,slider.getPosition().y);
                }
                else if(slider.getPosition().x > maxBarValue){
                    slider.setPosition(maxBarValue,slider.getPosition().y);
                }

                if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    clicked = false;
                }
            }

            const float largura = maxBarValue-minBarValue;
            const float sliderPos = slider.getPosition().x-minBarValue;
            value = (sliderPos*100)/largura;

            /*
            Set("caption="+to_string(value));

            Log::Push("Largura: "+to_string(largura));
            Log::Push("sliderPos: "+to_string(sliderPos));
            Log::Push("maxValue: "+to_string(maxValue));
            Log::Push("minValue: "+to_string(minValue));
            Log::Push("slider.getPosition().x: "+to_string(slider.getPosition().x));
            Log::Push("bar.getPosition().x: "+to_string(bar.getPosition().x));
            Log::Push("bar.getPosition().x+bar.getGlobalBounds(): "+to_string(bar.getPosition().x+bar.getGlobalBounds().width));
            */
        }
    }
}


void UI::Slider::UpdateStyle(){
    if(style == "light"){
        caption.setFillColor(sf::Color::White);
        caption.setOutlineColor(sf::Color::Black);
        bar.setFillColor(sf::Color::White);
        bar.setOutlineColor(Color::black);
        slider.setFillColor(Color::black);
        slider.setOutlineColor(Color::white);
    }
    else if(style == "dark"){
        caption.setFillColor(sf::Color::Black);
        caption.setOutlineColor(sf::Color::White);
        bar.setFillColor(sf::Color::Black);
        bar.setOutlineColor(Color::white);
        slider.setFillColor(Color::white);
        slider.setOutlineColor(Color::black);
    }
    else{
        Log::Push("Error: Slider with incorrect Style Argument");
    }
}


void UI::Slider::Set(string argument){
    try{
        if(argument == "invisible" || argument == "visible=false"){
            visible = false;
        }
        else if(argument == "visible" || argument == "visible=true"){
            visible = true;
        }
        else if(argument.find("caption=") != string::npos){
            caption.setString(argument.substr(argument.find("=")+1));
        }
        else if(argument.find("value=") != string::npos){
            value = stod(argument.substr(argument.find("=")+1));
        }
        else if(argument.find("maxValue=") != string::npos){
            maxValue = stod(argument.substr(argument.find("=")+1));
        }
        else if(argument.find("text=") != string::npos){
            caption.setString(argument.substr(argument.find("=")+1));
        }
    }
    catch(exception& e){
        Log::Push("Error in UI::Slider argument \""+argument+"\"");
    }
}


string UI::Slider::Return(string argument){
    if(argument == "progress"){
        return to_string(value);
    }
    if(argument == "value"){
        return to_string(maxValue*(value/100));
    }
    if(argument == "maxValue"){
        return to_string(maxValue);
    }
}

void UI::Slider::Draw(sf::RenderWindow* window){
    if(visible){
        window->draw(bar);
        window->draw(caption);
        window->draw(slider);
        window->draw(max_value);
        window->draw(min_value);
    }
    /*
    else{
        bar.setPosition(-1000,-1000);
        caption.setPosition(-1000,-1000);
    }*/
}
