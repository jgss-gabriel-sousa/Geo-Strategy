#include "States/Menus/Finances.h"

FinancesMenu::FinancesMenu(GameDataRef data,Country* c,GUIManager* gameGui) : data(data){
    playerCountry = c;
    baseGui = gameGui;
}

void FinancesMenu::Init(){
    text.setString(data->assets.GetLocalization(data->engine.language,"finances"));

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
        data->assets.GetLocalization(data->engine.language,"gdp")+": ",
        data->assets.GetLocalization(data->engine.language,"gdpForecast")+": ",
        data->assets.GetLocalization(data->engine.language,"growthForecast")+": ",
        data->assets.GetLocalization(data->engine.language,"lastYearGdpGrowth")+": ",
        data->assets.GetLocalization(data->engine.language,"inflation")+": ",
        data->assets.GetLocalization(data->engine.language,"nationalStockExchange")+": ",
        data->assets.GetLocalization(data->engine.language,"exports")+": ",
        data->assets.GetLocalization(data->engine.language,"imports")+": ",
        data->assets.GetLocalization(data->engine.language,"unemployment")+": ",
        data->assets.GetLocalization(data->engine.language,"unemploymentGrowth")+": "
    };
    gui.AddTextList("list1",texts,20,sf::Vector2f(pos1.x,pos1.y),5,"arial","right","light");

    texts = {"","","","","","","","","",""};
    gui.AddTextList("list2",texts,20,sf::Vector2f(pos2.x,pos2.y),5,"arial","left","light");



    //Static Menu
    gui.Set("list2","[0]:text="+database->ValueToScale(playerCountry->lastYearData.gdp*1000,"best",3));
    gui.Set("list2","[0]:style=numberGrey");

    gui.Set("list2","[1]:text="+database->ValueToScale(playerCountry->data.gdp*1000,"best",3));
    //gui.Set("list2","[1]:turningPointValue="+playerCountry->lastYearData.gdp);
    gui.Set("list2","[1]:style=number");

    gui.Set("list2","[2]:text="+database->ValueToPercentage(playerCountry->data.gdpGrowth,2));
    gui.Set("list2","[2]:style=number");

    gui.Set("list2","[3]:text="+database->ValueToPercentage(playerCountry->lastYearData.gdpGrowth,2));
    gui.Set("list2","[3]:style=number");

    gui.Set("list2","[4]:text="+database->ValueToPercentage(playerCountry->data.inflation,2));
    gui.Set("list2","[4]:style=numberInverse");

    gui.Set("list2","[5]:text="+database->SetPrecision(playerCountry->data.stockExchange,2));
    gui.Set("list2","[5]:style=number");

    gui.Set("list2","[6]:text="+database->SetPrecision(playerCountry->data.exports,2));
    gui.Set("list2","[6]:style=numberGrey");

    gui.Set("list2","[7]:text="+database->SetPrecision(playerCountry->data.imports,2));
    gui.Set("list2","[7]:style=numberGrey");

    gui.Set("list2","[8]:text="+database->ValueToPercentage(playerCountry->data.unemployment,2));
    gui.Set("list2","[8]:style=numberInverse");

    gui.Set("list2","[9]:text="+database->ValueToPercentage(playerCountry->data.unemploymentGrowth,2));
    gui.Set("list2","[9]:style=numberInverse");

    gui.Update();
}

void FinancesMenu::HandleInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        //data->machine.RemoveState();
    }
}

void FinancesMenu::Update(float dt){
    SubMenusUpdate(baseGui,&data->machine,&data->input,&data->window,&data->engine.GUIview,&window,&closeButton);
    baseGui->Update();
}

void FinancesMenu::Draw(float dt){
    data->window.draw(window);
    data->window.draw(closeButton);
    data->window.draw(text);
    data->window.draw(pieChart);
    gui.Draw();
}







