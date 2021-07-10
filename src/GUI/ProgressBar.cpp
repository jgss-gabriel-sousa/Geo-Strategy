#include "GUI/ProgressBar.h"

UI::ProgressBar::ProgressBar(float value,float maxValue,sf::Vector2f pos,sf::Vector2f Size,string caption,string style,int borderThickness,sf::Font& font,AssetManager* a){
    this->style = style;
    this->value = value;
    this->maxValue = maxValue;
    thickness = borderThickness;
    asset = a;

    pos = sf::Vector2f(pos.x-(Size.x/2),pos.y-(Size.y/2));

    bar.setPosition(pos.x+thickness,pos.y+thickness);

    barBackground.setSize(Size);
    barBackground.setOutlineThickness(-thickness);
    barBackground.setPosition(pos);

    this->caption.setCharacterSize(Size.y*0.7);
    this->caption.setString(caption);
    this->caption.setFont(font);
    this->caption.setOutlineThickness(this->caption.getCharacterSize()*0.15);
}

void UI::ProgressBar::Update(sf::RenderWindow* window,sf::View view){
    if(visible){
        bar.setSize(sf::Vector2f((barBackground.getSize().x-(thickness*2)) / (maxValue / (value+0.001)),barBackground.getSize().y));
        bar.setSize(sf::Vector2f(bar.getSize().x,bar.getSize().y-(thickness*2)));

        caption.setOrigin(caption.getGlobalBounds().width/2,0);
        caption.setPosition(barBackground.getPosition().x+(barBackground.getGlobalBounds().width/2),barBackground.getPosition().y);

        if(value >= maxValue){
            maxValue = value;
        }

        UpdateStyle();
    }
}


void UI::ProgressBar::UpdateStyle(){
    if(style == "light"){
        caption.setFillColor(sf::Color::Black);
        caption.setOutlineColor(sf::Color::White);
        bar.setFillColor(sf::Color::White);
        barBackground.setFillColor(sf::Color::Black);
        barBackground.setOutlineColor(Color::white);
    }
    else if(style == "dark"){
        caption.setFillColor(sf::Color::White);
        caption.setOutlineColor(sf::Color::Black);
        bar.setFillColor(sf::Color::Black);
        barBackground.setFillColor(sf::Color::White);
        barBackground.setOutlineColor(Color::black);
    }
    else if(style == "life"){
        caption.setFillColor(sf::Color::White);
        caption.setOutlineColor(sf::Color::Black);
        bar.setFillColor(sf::Color::Red);
        barBackground.setFillColor(Color::lightGreen);
        barBackground.setOutlineColor(Color::black);
    }
    else if(style == "loading"){
        caption.setFillColor(sf::Color::White);
        caption.setOutlineColor(sf::Color::Black);
        bar.setFillColor(Color::green);
        barBackground.setFillColor(sf::Color(225,0,0));
        barBackground.setOutlineColor(Color::black);
    }
    else{
        Log::Push("Error: ProgressBar with incorrect Style Argument");
    }
}


void UI::ProgressBar::Set(string argument){
    try{
        if(argument == "invisible"){
            visible = false;
        }
        else if(argument == "visible"){
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
        else if(argument.find("font=") != string::npos){
            caption.setFont(asset->GetFont(argument.substr(argument.find("=")+1)));
        }
    }
    catch(exception& e){
        Log::Push("Error in UI::ProgressBar argument \""+argument+"\"");
    }
}


string UI::ProgressBar::Return(string argument){
    if(argument == "progress"){
        return to_string(((value/maxValue)*100));
    }
    if(argument == "value"){
        return to_string(value);
    }
    if(argument == "maxValue"){
        return to_string(maxValue);
    }
}

void UI::ProgressBar::Draw(sf::RenderWindow* window){
    if(visible){
        window->draw(barBackground);
        window->draw(bar);
        window->draw(caption);
    }
    else{
        barBackground.setPosition(-1000,-1000);
        bar.setPosition(-1000,-1000);
        caption.setPosition(-1000,-1000);
    }
}
