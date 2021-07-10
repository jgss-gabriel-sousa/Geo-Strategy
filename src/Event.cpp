#include "Event.h"

void Event::Create(string tit,vector<string> desc,vector<string> opt,string conditions,string trigger,
                   Database* database){
    title = tit;
    description = desc;
    options = opt;
}

void Event::Init(sf::Vector2f position,sf::RenderWindow* window,AssetManager* asset){
    box.setSize({300,400});
    box.setOrigin(box.getGlobalBounds().width/2,box.getGlobalBounds().height/2);
    box.setPosition(position.x,position.y);
    box.setOutlineThickness(-2.5);
    box.setOutlineColor(Color::lightBlack);

    gui.Init(asset,window);
    gui.AddButtonBar("options",options,"vertical",{position.x,position.y*1.15},{box.getGlobalBounds().width/1.5,20},5);
    for(int i = 0; i<options.size(); i++){
        gui.Set("options","["+to_string(i)+"]:text.font.size=14");
    }
    gui.AddTextList("description",description,8,{position.x,position.y},2,"arial","left","dark");

    picture.setPosition({box.getPosition().x-box.getGlobalBounds().width/2+2.5,
                        box.getPosition().y-box.getGlobalBounds().height/2+2.5});
    picture.setSize({box.getGlobalBounds().width-5,(box.getGlobalBounds().height-5)/1.6});
    picture.setFillColor(Color::green);
}

void Event::Draw(sf::RenderWindow* window,sf::View* view){
    window->draw(box);
    window->draw(picture);
    gui.Update();
    gui.Draw();
}
