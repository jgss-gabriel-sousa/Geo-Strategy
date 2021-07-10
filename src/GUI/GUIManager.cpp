#include "GUI/GUIManager.h"

void GUIManager::Init(AssetManager* asset, sf::RenderWindow* window){
    this->asset = asset;
    this->window = window;
}

void GUIManager::Update(){
    for(pair<string,UI::BaseEntity*> element : elements){
        element.second->Update(window,window->getDefaultView());
    }
}

void GUIManager::Draw(){
    sf::View worldView = window->getView();
    window->setView(window->getDefaultView());

    for(pair<string,UI::BaseEntity*> element : elements){
        element.second->Draw(window);
    }

    window->setView(worldView);
}

string GUIManager::Get(string name,string argument){
    return elements[name]->Return(argument);
}

void GUIManager::Set(string name,string argument){
    elements[name]->Set(argument);
}

void GUIManager::Remove(string name){
    delete elements[name];
    elements.erase(name);
}

void GUIManager::Reset(){
    for(pair<string,UI::BaseEntity*> element : elements){
        //Remove(element.first);
        element.second->Set("invisible");
    }
}

void GUIManager::AddButton(string name,sf::Vector2f position,sf::Vector2f Size,string text,string style){
    elements[name] = new UI::Button(position,Size,text,style,asset->GetFont(BUTTON_FONT),asset);
}

void GUIManager::AddText(string name,sf::Vector2f position,string text,string font,unsigned int fontSize,string style){
    elements[name] = new UI::Text(asset,position,text,font,fontSize,style);
}

void GUIManager::AddProgressBar(string name,float value,float maxValue,sf::Vector2f position,sf::Vector2f Size,string caption,string style,int borderThickness){
    elements[name] = new UI::ProgressBar(value,maxValue,position,Size,caption,style,borderThickness,asset->GetFont(BAR_FONT),asset);
}

void GUIManager::AddButtonBar(string name,vector<string> buttonTexts,string alignment,sf::Vector2f firstPosition,sf::Vector2f Size,int spacing){
    elements[name] = new UI::ButtonBar(buttonTexts,alignment,Size,firstPosition,spacing,asset->GetFont(BUTTON_FONT),asset);
}

void GUIManager::AddSlider(string name,float minValue,float value,float maxValue,sf::Vector2f position,sf::Vector2f Size,string caption,string style,int thickness){
    elements[name] = new UI::Slider(minValue,value,maxValue,position,Size,caption,style,thickness,asset->GetFont(SLIDER_FONT));
}

void GUIManager::AddTextList(string name,vector<string>strings,int Size,sf::Vector2f firstPosition,int spacing,string font,
                             string alignment,string style){
    elements[name] = new UI::TextList(strings,Size,firstPosition,spacing,font,alignment,style,asset);
}







