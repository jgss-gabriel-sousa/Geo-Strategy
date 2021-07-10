#include "GUI/ButtonBar.h"

UI::ButtonBar::ButtonBar(vector<string>buttonTexts,string alignment,sf::Vector2f Size,sf::Vector2f firstPosition,int spacing,sf::Font& font,AssetManager* assetM){
    UI::Button b = UI::Button(firstPosition,Size,"","light",font,assetM);
    b.Set("position="+to_string(firstPosition.x)+","+to_string(firstPosition.y));

    if(alignment == "vertical"){
        float newPosY = firstPosition.y;
        for(int i = 0; i<buttonTexts.size(); i++){
            newPosY += spacing+Size.y;

            b.Set("position="+to_string(firstPosition.x)+","+to_string(newPosY));
            b.Set("text="+buttonTexts[i]);
            buttons.push_back(b);
        }
    }
    else{
        float newPosX = firstPosition.x;
        for(int i = 0; i<buttonTexts.size(); i++){
            newPosX += spacing+Size.x;

            b.Set("position="+to_string(newPosX)+","+to_string(firstPosition.y));
            b.Set("text="+buttonTexts[i]);
            buttons.push_back(b);
        }
    }
}

void UI::ButtonBar::Update(sf::RenderWindow* window,sf::View view){
    for(int i = 0; i < buttons.size(); i++){
        buttons[i].Update(window,view);
    }
}

void UI::ButtonBar::Set(string argument){
    try{
        if(argument == "invisible"){
            visible = false;
        }
        else if(argument == "visible"){
            visible = true;
        }
        else if(argument.find("style=") != string::npos){
            argument = argument.substr(argument.find("=")+1);
            int button = stoi(argument.substr(0,argument.find("=")));
            argument = argument.substr(argument.find("=")+1);
            buttons[button].Set("style="+argument);
        }
        else if(argument.find("]:") != string::npos){
            int text = stoi(argument.substr(argument.find("[")+1,argument.find("]")));
            argument = argument.substr(argument.find(":")+1);
            buttons[text].Set(argument);
        }
    }
    catch(exception& e){
        Log::Push("Error in UI::ButtonBar argument \""+argument+"\"");
    }
}

void UI::ButtonBar::UpdateStyle(){
    ;
}

string UI::ButtonBar::Return(string argument){
    if(argument == "buttonClicked"){
        for(int i = 0; i < buttons.size(); i++){
            if(buttons[i].Return("clicked") == "true"){
                return to_string(i);
            }
        }
        return "-1";
    }
    else if(argument.find("]:") != string::npos){
        int text = stoi(argument.substr(argument.find("[")+1,argument.find("]")));
        argument = argument.substr(argument.find(":")+1);
        return buttons[text].Return(argument);
    }
}

void UI::ButtonBar::Draw(sf::RenderWindow* window){
    if(visible){
        for(int i = 0; i < buttons.size(); i++){
            buttons[i].Set("visible");
            buttons[i].Draw(window);
        }
    }
    else{
        for(int i = 0; i < buttons.size(); i++){
            buttons[i].Set("invisible");
        }
    }
}







