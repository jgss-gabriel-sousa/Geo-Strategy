#include "GUI/Button.h"

UI::Button::Button(sf::Vector2f position,sf::Vector2f Size,string sText,string style,sf::Font& font,AssetManager* assetM){
    framesBetweenClick = 0;
    this->style = style;
    asset = assetM;

    sprite.setSize(Size);
    sprite.setOrigin(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2);
    sprite.setPosition((int)position.x,(int)position.y);
    sprite.setOutlineColor(Color::lightBlack);
    sprite.setOutlineThickness(1);
    text.setString(sText);
    text.setFont(font);
    text.setCharacterSize(sprite.getSize().y/3);
}

void UI::Button::Update(sf::RenderWindow* window,sf::View view){
    if(visible){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(sprite.getGlobalBounds().contains(sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window),view)))){
                framesBetweenClick = 0;
                clicked = true;
            }
        }

        if(fontSize == -1){
            if(text.getGlobalBounds().width*1.1 > sprite.getGlobalBounds().width){
                if(text.getCharacterSize()-(text.getGlobalBounds().width*1.1-sprite.getGlobalBounds().width) < 12)
                    text.setCharacterSize(12);
                else
                    text.setCharacterSize(text.getCharacterSize()-(text.getGlobalBounds().width-sprite.getGlobalBounds().width));
            }
        }
        else{
            text.setCharacterSize(fontSize);
        }

        if(textAlignment == "center"){
            text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/1.5);
        }
        else if(textAlignment == "left"){
            text.setOrigin(0,text.getGlobalBounds().height/1.5);
        }
        else if(textAlignment == "right"){
            text.setOrigin(text.getGlobalBounds().width,text.getGlobalBounds().height/1.5);
        }
        const int x = sprite.getPosition().x+addX;
        const int y = sprite.getPosition().y+addY;
        text.setPosition(x,y);

        if(framesBetweenClick != -1)
            framesBetweenClick++;

        if(framesBetweenClick > FRAMES_CLICK_ANIMATION && clickType != "static"){
            clicked = false;
            framesBetweenClick = -1;
        }

        UpdateStyle();
    }
}

void UI::Button::Set(string argument){
    try{
        if(argument == "visible=false" || argument == "invisible"){
            visible = false;
            visibilityChange = true;
        }
        else if(argument == "visible=true" || argument == "visible"){
            visible = true;
            visibilityChange = true;
        }
        else if(argument.find("text.positionAdd.y=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            addY += stoi(argument);
        }
        else if(argument.find("text.positionAdd.x=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            addX += stoi(argument);
        }
        else if(argument == "text.font.size=auto"){
            fontSize = -1;
        }
        else if(argument.find("text.font.size=") != string::npos){
            fontSize = stoi(argument.substr(argument.find("=")+1));
        }
        else if(argument.find("text.font=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            text.setFont(asset->GetFont(argument));
        }
        else if(argument.find("text.alignment=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            textAlignment = argument;
        }
        else if(argument.find("text=") != string::npos){
            text.setString(argument.substr(argument.find("=")+1));
        }
        else if(argument.find("position=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            sprite.setPosition(stoi(argument.substr(0,argument.find(","))),stoi(argument.substr(argument.find(",")+1)));
        }
        else if(argument.find("texture=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            sprite.setTexture(&asset->GetTexture(argument),true);
        }
        else if(argument.find("style=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            style = argument;
        }
        else if(argument.find("outline=") != string::npos){
            argument = argument.substr(argument.find("=")+1);

            if(argument == "true")
                text.setOutlineThickness(text.getCharacterSize()*0.07);
            else
                text.setOutlineThickness(0);
        }
        else if(argument.find("clickType=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            clickType = argument;
        }
        else if(argument.find("clicked=") != string::npos){
            argument = argument.substr(argument.find("=")+1);

            if(argument == "true")
                clicked = true;
            else
                clicked = false;
        }
    }
    catch(exception& e){
        Log::Push("Error in UI::Button argument \""+argument+"\"");
    }
}

void UI::Button::UpdateStyle(){
    if(style == "light"){
        text.setFillColor(Color::lightBlack);
        text.setOutlineColor(Color::white);

        if(clicked)
            sprite.setFillColor(Color::darkWhite);
        else
            sprite.setFillColor(Color::white);
    }
    else if(style == "lightClicked"){
        text.setFillColor(Color::white);
        text.setOutlineColor(Color::lightBlack);
        sprite.setFillColor(Color::grey);
    }
    else if(style == "dark"){
        text.setFillColor(Color::white);
        text.setOutlineColor(Color::lightBlack);

        if(clicked)
            sprite.setFillColor(Color::grey);
        else
            sprite.setFillColor(Color::lightBlack);
    }
    else if(style == "confirm"){
        text.setFillColor(Color::white);
        text.setOutlineColor(Color::lightBlack);

        if(clicked)
            sprite.setFillColor(Color::darkGreen);
        else
            sprite.setFillColor(Color::green);
    }
    else{
        Log::Push("Error: Button with incorrect Style Argument");
    }
}

string UI::Button::Return(string argument){
    if(argument == "position"){
        return to_string(sprite.getPosition().x)+","+to_string(sprite.getPosition().y);
    }
    else if(argument == "clicked"){
        if(clicked == true)
            return "true";
        else
            return "false";
    }
    else if(argument == "position.x"){
        return to_string(sprite.getPosition().x);
    }
    else if(argument == "position.y"){
        return to_string(sprite.getPosition().y);
    }
    else if(argument == "state"){
        if(clicked){
            return to_string(true);
        }
        else{
            return to_string(false);
        }
    }
}

void UI::Button::Draw(sf::RenderWindow* window){
    if(visible){
        window->draw(sprite);
        window->draw(text);
    }
/*
        if(visibilityChange){
            sprite.setPosition(spritePos);
            text.setPosition(textPos);
            visibilityChange = false;
        }
        spritePos = sprite.getPosition();
        textPos = text.getPosition();
    }
    else{
        sprite.setPosition(-1000,-1000);
        text.setPosition(-1000,-1000);
    }
    */
}





