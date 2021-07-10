#include "States/Menus/Currency.h"

CurrencyMenu::CurrencyMenu(GameDataRef data,Country* c,GUIManager* gameGui) : data(data){
    playerCountry = c;
    baseGui = gameGui;
}

void CurrencyMenu::Init(){
    text.setString(data->assets.GetLocalization(data->engine.language,"currency"));

    SubMenusInit(baseGui,&data->gui,&data->assets,&data->window,&text,&window,&closeButton);
    gui.Init(&data->assets,&data->window);

    sf::Vector2f pos1 = sf::Vector2f(window.getPosition().x+200-window.getGlobalBounds().width/2,
                                    window.getPosition().y-5-window.getGlobalBounds().height/2);
    sf::Vector2f pos2 = sf::Vector2f(window.getPosition().x+210-window.getGlobalBounds().width/2,
                                    pos1.y);

    vector<string> texts{
        data->assets.GetLocalization(data->engine.language,"inflation")+": ",
        data->assets.GetLocalization(data->engine.language,"interestRate")+": ",
        data->assets.GetLocalization(data->engine.language,"exchangeDolar")+": ",
        data->assets.GetLocalization(data->engine.language,"exchangeEuro")+": "
    };
    gui.AddTextList("list1",texts,20,sf::Vector2f(pos1.x,pos1.y),5,"arial","right","light");

    texts = {"","","",""};
    gui.AddTextList("list2",texts,20,sf::Vector2f(pos2.x,pos2.y),5,"arial","left","light");

    gui.AddSlider("interestRate",0,playerCountry->data.interestRate,50,{window.getPosition().x-250,500},{500,25},"","light",1);

    gui.AddButton("confirm",{window.getPosition().x,window.getPosition().y-50+window.getGlobalBounds().height/2},{75,50},
                  data->assets.GetLocalization(data->engine.language,"confirm"),"confirm");
}

void CurrencyMenu::HandleInput(){
    ;
}

void CurrencyMenu::Update(float dt){
    SubMenusUpdate(baseGui,&data->machine,&data->input,&data->window,&data->engine.GUIview,&window,&closeButton);
    gui.Update();

    gui.Set("list2","[0]:text="+database->ValueToPercentage(playerCountry->data.inflation,2));
    gui.Set("list2","[0]:style=numberInverse");

    gui.Set("list2","[1]:text="+database->ValueToPercentage(playerCountry->data.interestRate,1));
    gui.Set("list2","[1]:style=numberGrey");
    newInterestRate = stod(database->SetPrecision(stod(gui.Get("interestRate","value")),1));

    gui.Set("list2","[2]:text="+to_string(database->CurrencyExchange("USD",playerCountry->data.currency->tag)));
    gui.Set("list2","[2]:turningPointValue=0");
    gui.Set("list2","[2]:style=number");

    gui.Set("list2","[3]:text="+to_string(database->CurrencyExchange("EUR",playerCountry->data.currency->tag)));
    gui.Set("list2","[3]:turningPointValue=0");
    gui.Set("list2","[3]:style=number");

    gui.Set("interestRate","text="+data->assets.GetLocalization(data->engine.language,"interestRate")+": "+
            database->ValueToPercentage(stod(gui.Get("interestRate","value")),1));

    if(gui.Get("confirm","clicked") == "true"){
        playerCountry->data.interestRate = newInterestRate;
    }
}

void CurrencyMenu::Draw(float dt){
    data->window.draw(window);
    data->window.draw(closeButton);
    data->window.draw(text);
    gui.Draw();
}







