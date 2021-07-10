#include "GUI/Text.h"

UI::Text::Text(AssetManager* asset,sf::Vector2f position,string textString,string font,unsigned int fontSize,string style){
    assets = asset;
    text.setString(textString);
    text.setFont(asset->GetFont(font));
    text.setCharacterSize(fontSize);
    text.setPosition((int)position.x,(int)position.y);
    text.setOutlineThickness(1);
    textAlignment = "center";

    this->style = style;

    turningPointValue = 0;
}

void UI::Text::Update(sf::RenderWindow* window,sf::View view){
    if(visible){
        if(textAlignment == "center"){
            text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/1.5);
        }
        else if(textAlignment == "left"){
            text.setOrigin(0,text.getGlobalBounds().height/1.5);
        }
        else if(textAlignment == "right"){
            text.setOrigin(text.getGlobalBounds().width,text.getGlobalBounds().height/1.5);
        }

        //Styles
        if(style == "light"){
            text.setColor(Color::white);
            text.setOutlineColor(Color::lightBlack);
        }
        else if(style == "dark"){
            text.setColor(Color::lightBlack);
            text.setOutlineColor(Color::white);
        }
        if(style == "number"){
            try{
                string str = text.getString();
                value = stod(str);
            }
            catch(exception& e){
                value = turningPointValue;
            }

            if(value < turningPointValue){
                text.setFillColor(Color::red);
            }
            else if(value > turningPointValue){
                text.setFillColor(Color::green);
            }
            else{
                text.setFillColor(Color::grey);
            }
        }
        else if(style == "numberInverse"){
            try{
                string str = text.getString();
                value = stod(str);
            }
            catch(exception& e){
                value = turningPointValue;
            }

            if(value < turningPointValue){
                text.setFillColor(Color::lightGrey);
            }
            else if(value > turningPointValue){
                text.setFillColor(Color::red);
            }
            else{
                text.setFillColor(Color::grey);
            }
        }
        else if(style == "numberGrey"){
            try{
                string str = text.getString();
                value = stod(str);
            }
            catch(exception& e){
                value = turningPointValue;
            }

            text.setFillColor(Color::lightGrey);
        }
    }
}

void UI::Text::Set(string argument){
    try{
        if(argument == "invisible" || argument == "visible=false"){
            visible = false;
        }
        else if(argument == "visible" || argument == "visible=true"){
            visible = true;
        }
        else if(argument.find("text.alignment=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            textAlignment = argument;
        }
        else if(argument.find("text=") != string::npos){
            text.setString(argument.substr(argument.find("=")+1));
        }
        else if(argument.find("font=") != string::npos){
            text.setFont(assets->GetFont(argument.substr(argument.find("=")+1)));
        }
        else if(argument.find("position=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            text.setPosition(stoi(argument.substr(0,argument.find(","))),stoi(argument.substr(argument.find(",")+1)));
        }
        else if(argument.find("style=") != string::npos){
            style = argument.substr(argument.find("=")+1);
        }
        else if(argument.find("turningPointValue=") != string::npos){
            turningPointValue = stod(argument.substr(argument.find("=")+1));
        }
    }
    catch(exception& e){
        Log::Push("Error in UI::Text argument \""+argument+"\"");
    }
}


string UI::Text::Return(string argument){
    return text.getString();
}

void UI::Text::Draw(sf::RenderWindow* window){
    if(visible){
        window->draw(text);
    }
/*
        if(visibilityChange){
            text.setPosition((int)textPos.x,(int)textPos.y);
            visibilityChange = false;
        }
        textPos = text.getPosition();
    }
    else{
        //text.setPosition(-1000,-1000);
    }
    */
}
