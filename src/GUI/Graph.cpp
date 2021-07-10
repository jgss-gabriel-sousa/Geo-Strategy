#include "GUI/Graph.h"

UI::Graph::Graph(sf::Vector2f position,sf::Vector2f Size,vector<double> pointsX,vector<double> pointsY,string title,
                 string style,int border,sf::Font& font,AssetManager* assetM){
    this->style = style;
    asset = assetM;

    sprite.setSize(Size);
    sprite.setOrigin(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2);
    sprite.setPosition((int)position.x,(int)position.y);
    sprite.setOutlineColor(Color::lightBlack);
    sprite.setOutlineThickness(border);
    text.setString(title);
    text.setFont(font);
    text.setCharacterSize(sprite.getSize().y/3);
}

void UI::Graph::Update(sf::RenderWindow* window,sf::View view){
    if(visible){
        UpdateStyle();
    }
}

void UI::Graph::Set(string argument){
    try{
        if(argument == "visible=false" || argument == "invisible"){
            visible = false;
            visibilityChange = true;
        }
        else if(argument == "visible=true" || argument == "visible"){
            visible = true;
            visibilityChange = true;
        }
    }
    catch(exception& e){
        Log::Push("Error in UI::Graph argument \""+argument+"\"");
    }
}

void UI::Graph::UpdateStyle(){
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
        Log::Push("Error: Graph with incorrect Style Argument");
    }
}

string UI::Graph::Return(string argument){
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

void UI::Graph::Draw(sf::RenderWindow* window){
    if(visible){
        window->draw(sprite);
        window->draw(text);

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
}





