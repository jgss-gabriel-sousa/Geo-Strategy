#include "States/Menus/State Budget.h"

StateBudgetMenu::StateBudgetMenu(GameDataRef data,Country* c,GUIManager* gameGui) : data(data){
    playerCountry = c;
    baseGui = gameGui;
}

void StateBudgetMenu::Init(){
    text.setString(data->assets.GetLocalization(data->engine.language,"stateBudget"));

    pieChart.slices.resize(3);
    pieChart.slices[0].color = sf::Color::Blue;
    pieChart.slices[1].color = sf::Color::Yellow;
    pieChart.slices[2].color = sf::Color::Yellow;
    pieChart.slices[0].size = playerCountry->data.healthBudget/playerCountry->data.gdp;
    pieChart.slices[1].size = playerCountry->data.educationBudget/playerCountry->data.gdp;
    pieChart.slices[2].size = playerCountry->data.millitaryBudget/playerCountry->data.gdp;
    pieChart.setSize({ 150.f, 150.f });
    pieChart.update();
    pieChart.setOrigin(pieChart.getSize() / 2.f);
    pieChart.setPosition(window.getPosition());

    SubMenusInit(baseGui,&data->gui,&data->assets,&data->window,&text,&window,&closeButton);
    gui.Init(&data->assets,&data->window);

    sf::Vector2f pos1 = sf::Vector2f(window.getPosition().x+250-window.getGlobalBounds().width/2,
                                    window.getPosition().y-5-window.getGlobalBounds().height/2);
    sf::Vector2f pos2 = sf::Vector2f(window.getPosition().x+260-window.getGlobalBounds().width/2,
                                    pos1.y);

    vector<string> texts{
        data->assets.GetLocalization(data->engine.language,"balance")+": ",
        data->assets.GetLocalization(data->engine.language,"revenues")+": ",
        data->assets.GetLocalization(data->engine.language,"expenses")+": "
    };
    gui.AddTextList("list1",texts,20,sf::Vector2f(pos1.x,pos1.y),5,"arial","right","light");

    texts = {"","",""};
    gui.AddTextList("list2",texts,20,sf::Vector2f(pos2.x,pos2.y),5,"arial","left","light");


    //Static Menu
    gui.Set("list2","[0]:text="+database->ValueToScale((playerCountry->data.budgetRevenue-
                                                        playerCountry->data.budgetExpenditure)*1000,"best",3));
    gui.Set("list2","[0]:style=numberInverse");

    gui.Set("list2","[1]:text="+database->ValueToScale(playerCountry->data.budgetRevenue*1000,"best",3));
    gui.Set("list2","[1]:style=numberGrey");

    gui.Set("list2","[2]:text="+database->ValueToScale(playerCountry->data.budgetExpenditure*1000,"best",3));
    gui.Set("list2","[2]:style=numberGrey");

    gui.Update();

    for(int i = 0; i<data->database.countryRanking.size(); i++){
        Log::Push(data->database.countryRanking[i].second+" = "+to_string(data->database.countryRanking[i].first));
    }
}

void StateBudgetMenu::HandleInput(){
    ;
}

void StateBudgetMenu::Update(float dt){
    //if(state)
    SubMenusUpdate(baseGui,&data->machine,&data->input,&data->window,&data->engine.GUIview,&window,&closeButton);
    //gui.Update();
}

void StateBudgetMenu::Draw(float dt){
    data->window.draw(window);
    data->window.draw(closeButton);
    data->window.draw(text);
    data->window.draw(pieChart);
    gui.Draw();
}







