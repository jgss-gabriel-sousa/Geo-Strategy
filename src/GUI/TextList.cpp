#include "GUI/TextList.h"

UI::TextList::TextList(vector<string>strings,int Size,sf::Vector2f firstPosition,int spacing,string font,string alignment,
                       string style,AssetManager* assetM){
    UI::Text t = UI::Text(assetM,firstPosition,"","arial",Size,"light");
    t.Set("position="+to_string(firstPosition.x)+","+to_string(firstPosition.y));
    t.Set("font="+font);
    t.Set("text.alignment="+alignment);

    float newPosY = firstPosition.y;
    for(int i = 0; i<strings.size(); i++){
        newPosY += spacing+Size;

        t.Set("position="+to_string(firstPosition.x)+","+to_string(newPosY));
        t.Set("text="+strings[i]);
        texts.push_back(t);
    }
}

void UI::TextList::Update(sf::RenderWindow* window,sf::View view){
    for(int i = 0; i < texts.size(); i++){
        texts[i].Update(window,view);
    }
}

void UI::TextList::Set(string argument){
    try{
        if(argument == "invisible"){
            visible = false;
        }
        else if(argument == "visible"){
            visible = true;
        }
        else if(argument.find("]:") != string::npos){
            int text = stoi(argument.substr(argument.find("[")+1,argument.find("]")));
            argument = argument.substr(argument.find(":")+1);
            texts[text].Set(argument);
        }
    }
    catch(exception& e){
        Log::Push("Error in UI::TextList argument \""+argument+"\"");
    }
}

string UI::TextList::Return(string argument){
    if(argument == "textClicked"){
        for(int i = 0; i < texts.size(); i++){
            if(texts[i].Return("clicked") == "true"){
                return to_string(i);
            }
        }
        return "-1";
    }
}

void UI::TextList::Draw(sf::RenderWindow* window){
    if(visible){
        for(int i = 0; i < texts.size(); i++){
            texts[i].Set("visible");
            texts[i].Draw(window);
        }
    }
    else{
        for(int i = 0; i < texts.size(); i++){
            texts[i].Set("invisible");
        }
    }
}







