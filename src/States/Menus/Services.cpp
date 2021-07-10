#include "States/Menus/Services.h"

ServicesMenu::ServicesMenu(GameDataRef data,Country* c,GUIManager* gameGui) : data(data){
    playerCountry = c;
    baseGui = gameGui;
}

void ServicesMenu::Init(){
    text.setString(data->assets.GetLocalization(data->engine.language,"services"));

    pieChart.slices.resize(3);
    pieChart.slices[0].color = sf::Color::Red;
    pieChart.slices[1].color = sf::Color::Green;
    pieChart.slices[2].color = sf::Color::Blue;
    pieChart.slices[0].size = 0.65f;
    pieChart.slices[1].size = 0.075f;
    pieChart.slices[2].size = 0.275f;
    pieChart.setSize({ 150.f, 150.f });
    pieChart.update();
    pieChart.setOrigin(pieChart.getSize() / 2.f);
    pieChart.setPosition(data->window.getView().getCenter());

    SubMenusInit(baseGui,&data->gui,&data->assets,&data->window,&text,&window,&closeButton);
    gui.Init(&data->assets,&data->window);

    sf::Vector2f pos1 = sf::Vector2f(window.getPosition().x+250-window.getGlobalBounds().width/2,
                                    window.getPosition().y-5-window.getGlobalBounds().height/2);
    sf::Vector2f pos2 = sf::Vector2f(window.getPosition().x+260-window.getGlobalBounds().width/2,
                                    pos1.y);

    vector<string> texts{
        data->assets.GetLocalization(data->engine.language,"population")+": "
    };
    gui.AddTextList("list1",texts,20,sf::Vector2f(pos1.x,pos1.y),5,"arial","right","light");

    texts = {""};
    gui.AddTextList("list2",texts,20,sf::Vector2f(pos2.x,pos2.y),5,"arial","left","light");


    //Static Menu
    gui.Set("list2","[0]:text="+to_string(playerCountry->data.population));

    gui.Update();
}

void ServicesMenu::HandleInput(){
    ;
}

void ServicesMenu::Update(float dt){
    //if(state)
    SubMenusUpdate(baseGui,&data->machine,&data->input,&data->window,&data->engine.GUIview,&window,&closeButton);
    //gui.Update();
}

void ServicesMenu::Draw(float dt){
    data->window.draw(window);
    data->window.draw(closeButton);
    data->window.draw(text);
    data->window.draw(pieChart);
    gui.Draw();
}







