#include "States/Menus/Industry.h"

IndustryMenu::IndustryMenu(GameDataRef data,Country* c,GUIManager* gameGui) : data(data){
    playerCountry = c;
    baseGui = gameGui;
}

void IndustryMenu::Init(){
    text.setString(data->assets.GetLocalization(data->engine.language,"industry"));

    SubMenusInit(baseGui,&data->gui,&data->assets,&data->window,&text,&window,&closeButton);
    gui.Init(&data->assets,&data->window);

    pieChart.slices.resize(2);
    pieChart.slices[0].color = sf::Color::Blue;
    pieChart.slices[1].color = sf::Color::Yellow;
    pieChart.slices[0].size = 1-(playerCountry->data.industryGdp/playerCountry->data.gdp);
    pieChart.slices[1].size = playerCountry->data.industryGdp/playerCountry->data.gdp;
    pieChart.setSize({ 150.f, 150.f });
    pieChart.update();
    pieChart.setOrigin(pieChart.getSize() / 2.f);
    pieChart.setPosition(window.getPosition());

    sf::Vector2f pos1 = sf::Vector2f(window.getPosition().x+250-window.getGlobalBounds().width/2,
                                    window.getPosition().y-5-window.getGlobalBounds().height/2);
    sf::Vector2f pos2 = sf::Vector2f(window.getPosition().x+260-window.getGlobalBounds().width/2,
                                    pos1.y);

    vector<string> texts{
        data->assets.GetLocalization(data->engine.language,"industrialGdp")+": ",
        data->assets.GetLocalization(data->engine.language,"industrialGdpRate")+": "
    };
    gui.AddTextList("list1",texts,20,sf::Vector2f(pos1.x,pos1.y),5,"arial","right","light");

    texts = {"","","","","","","","","",""};
    gui.AddTextList("list2",texts,20,sf::Vector2f(pos2.x,pos2.y),5,"arial","left","light");



    //Static Menu
    gui.Set("list2","[0]:text="+database->ValueToScale(playerCountry->lastYearData.industryGdp*1000,"best",3));
    gui.Set("list2","[1]:style=numberGrey");

    gui.Set("list2","[1]:text="+database->ValueToPercentage((playerCountry->lastYearData.industryGdp/playerCountry->lastYearData.gdp)*100,2));
    gui.Set("list2","[1]:style=numberGrey");

    gui.Update();
}

void IndustryMenu::HandleInput(){
    ;
}

void IndustryMenu::Update(float dt){
    SubMenusUpdate(baseGui,&data->machine,&data->input,&data->window,&data->engine.GUIview,&window,&closeButton);

    //gui.Update();
}

void IndustryMenu::Draw(float dt){
    data->window.draw(window);
    data->window.draw(closeButton);
    data->window.draw(text);
    data->window.draw(pieChart);
    gui.Draw();
}







