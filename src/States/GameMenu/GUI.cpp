#include "States/GameMenu.h"

void GameMenu::UpdateGUI(){
    gui->Set("stateName","text="+stateName);
    gui->Set("gameDate","text="+data->database.GetDate(data->engine.dataFormat));

    if(gui->Get("countryFlag","clicked") == "true"){
        MoveCameraTo(playerCountry->data.capitalState->sprite.getPosition().x+
                            playerCountry->data.capitalState->sprite.getGlobalBounds().width/2,
                       playerCountry->data.capitalState->sprite.getPosition().y+
                            playerCountry->data.capitalState->sprite.getGlobalBounds().height/2);
    }

    //Speed Bar
{
    int buttonClicked = stoi(gui->Get("gameSpeed","buttonClicked"));
    static int lastClickedSpeed;

    if(buttonClicked != -1){
        lastClickedSpeed = buttonClicked;
    }

    gui->Set("gameSpeed","style=0=light");
    gui->Set("gameSpeed","style=1=light");
    gui->Set("gameSpeed","style=2=light");
    gui->Set("gameSpeed","style=3=light");

    if(lastClickedSpeed == 0){
        gui->Set("gameSpeed","style=0=lightClicked");
        gameVelocity = 0;
    }
    else if(lastClickedSpeed == 1){
        gui->Set("gameSpeed","style=1=lightClicked");
        gameVelocity = 3;
    }
    else if(lastClickedSpeed == 2){
        gui->Set("gameSpeed","style=1=lightClicked");
        gui->Set("gameSpeed","style=2=lightClicked");
        gameVelocity = 0.5;
    }
    else if(lastClickedSpeed == 3){
        gui->Set("gameSpeed","style=1=lightClicked");
        gui->Set("gameSpeed","style=2=lightClicked");
        gui->Set("gameSpeed","style=3=lightClicked");
        gameVelocity = 0.01;
    }

    buttonClicked = stoi(gui->Get("gameSpeed","buttonClicked"));
}

    //Primary Bars
    int menuClicked = stoi(gui->Get("menuBar","buttonClicked"));
    static int lastClicked;
    string clicked;

    if(menuClicked != -1){
        lastClicked = menuClicked;
    }

    gui->Set("menuBar","visible");
    gui->Set("economyBar","invisible");
    gui->Set("infrastructureBar","invisible");
    gui->Set("securityBar","invisible");
    gui->Set("diplomacyBar","invisible");
    gui->Set("governmentBar","invisible");
    gui->Set("socialBar","invisible");
    gui->Set("investmentsBar","invisible");
    gui->Set("menuBar","style=0=light");
    gui->Set("menuBar","style=1=light");
    gui->Set("menuBar","style=2=light");
    gui->Set("menuBar","style=3=light");
    gui->Set("menuBar","style=4=light");
    gui->Set("menuBar","style=5=light");
    gui->Set("menuBar","style=6=light");
    gui->Set("menuBar","style=7=light");

    if(lastClicked == 0){
        clicked="economyBar";
        gui->Set("menuBar","style=0=lightClicked");
        gui->Set("economyBar","visible");
    }
    else if(lastClicked == 1){
        clicked="governmentBar";
        gui->Set("menuBar","style=1=lightClicked");
        gui->Set("governmentBar","visible");
    }
    else if(lastClicked == 2){
        clicked="infrastructureBar";
        gui->Set("menuBar","style=2=lightClicked");
        gui->Set("infrastructureBar","visible");
    }
    else if(lastClicked == 3){
        clicked="socialBar";
        gui->Set("menuBar","style=3=lightClicked");
        gui->Set("socialBar","visible");
    }
    else if(lastClicked == 4){
        clicked="securityBar";
        gui->Set("menuBar","style=4=lightClicked");
        gui->Set("securityBar","visible");
    }
    else if(lastClicked == 5){
        clicked="diplomacyBar";
        gui->Set("menuBar","style=5=lightClicked");
        gui->Set("diplomacyBar","visible");
    }
    else if(lastClicked == 6){
        clicked="investmentsBar";
        gui->Set("menuBar","style=6=lightClicked");
        gui->Set("investmentsBar","visible");
    }
    else if(lastClicked == 7){
        return;
        //gui->Set("menuBar","style=6=lightClicked");
        //gui->Set("investmentsBar","visible");
        //data->machine.AddState(StateRef(new StatisticsMenu(this->data,playerCountry)),false);
    }

    //Secondary Bars
    menuClicked = stoi(gui->Get(clicked,"buttonClicked"));

    if(clicked == "economyBar"){
        if(menuClicked == 0){
            data->machine.AddState(StateRef(new FinancesMenu(this->data,playerCountry,gui)),false);
        }
        else if(menuClicked == 1){
            data->machine.AddState(StateRef(new CurrencyMenu(this->data,playerCountry,gui)),false);
        }
        else if(menuClicked == 2){
            data->machine.AddState(StateRef(new IndustryMenu(this->data,playerCountry,gui)),false);
        }
        else if(menuClicked == 3){
            data->machine.AddState(StateRef(new ServicesMenu(this->data,playerCountry,gui)),false);
        }
        else if(menuClicked == 4){
            data->machine.AddState(StateRef(new AgricultureMenu(this->data,playerCountry,gui)),false);
        }
    }
    else if(clicked == "governmentBar"){
        if(menuClicked == 0){
            data->machine.AddState(StateRef(new StateBudgetMenu(this->data,playerCountry,gui)),false);
        }
        else if(menuClicked == 1){
            data->machine.AddState(StateRef(new CivilServantMenu(this->data,playerCountry,gui)),false);
        }
        else if(menuClicked == 2){
            ;
        }
    }
}


void GameMenu::InitGUI(){
    sf::Vector2f barSize = sf::Vector2f(100,50);
    sf::Vector2f primaryBarPos = sf::Vector2f(60,74);
    sf::Vector2f secondaryBarPos = sf::Vector2f(165,74);

    data->gui.Reset();

    data->gui.AddButton("playerFace",sf::Vector2f(data->engine.screenWidth-60,60),sf::Vector2f(100,100),"","light");
    data->gui.Set("playerFace","texture="+leaderName);

    data->gui.AddButton("countryFlag",sf::Vector2f(70,42),sf::Vector2f(120,64),
                        data->assets.GetLocalization(data->engine.language,countryName),"light");
    data->gui.Set("countryFlag","texture="+countryName);
    data->gui.Set("countryFlag","outline=true");
    data->gui.Set("countryFlag","text.positionAdd.y=+48");
    data->gui.Set("countryFlag","text.positionAdd.x=-60");
    data->gui.Set("countryFlag","text.alignment=left");
    data->gui.Set("countryFlag","text.font.size=20");

    gui->AddText("stateName",sf::Vector2f(data->engine.screenWidth-10,data->engine.screenHeight-100),"TEST","arial",20,"light");
    gui->Set("stateName","text.alignment=right");

    gui->AddText("gameDate",sf::Vector2f(data->engine.screenWidth-10,130),"YY/MM/DD","arial",20,"light");
    gui->Set("gameDate","text.alignment=right");

    gui->AddButtonBar("gameSpeed",{"","","",""},"horizontal",{data->engine.screenWidth-110,160},{20,20},2);
    gui->Set("gameSpeed","[0]:clicked=true");

    //Primary Bar
    vector<string> texts{
        data->assets.GetLocalization(data->engine.language,"Economy"),
        data->assets.GetLocalization(data->engine.language,"Government"),
        data->assets.GetLocalization(data->engine.language,"Infrastructure"),
        data->assets.GetLocalization(data->engine.language,"Social"),
        data->assets.GetLocalization(data->engine.language,"Security"),
        data->assets.GetLocalization(data->engine.language,"Diplomacy"),
        data->assets.GetLocalization(data->engine.language,"Investments"),
        data->assets.GetLocalization(data->engine.language,"Statistics")
    };
    data->gui.AddButtonBar("menuBar",texts,"vertical",primaryBarPos,barSize,5);

    //Secondary Bars
    texts.clear();
    texts = {
        data->assets.GetLocalization(data->engine.language,"Finances"),
        data->assets.GetLocalization(data->engine.language,"Currency"),
        data->assets.GetLocalization(data->engine.language,"Industry"),
        data->assets.GetLocalization(data->engine.language,"Services"),
        data->assets.GetLocalization(data->engine.language,"Agriculture")
    };
    data->gui.AddButtonBar("economyBar",texts,"vertical",secondaryBarPos,barSize,5);

    texts.clear();
    texts = {
        data->assets.GetLocalization(data->engine.language,"Energy"),
        data->assets.GetLocalization(data->engine.language,"Transportation"),
        data->assets.GetLocalization(data->engine.language,"Environment")
    };
    data->gui.AddButtonBar("infrastructureBar",texts,"vertical",secondaryBarPos,barSize,5);

    texts.clear();
    texts = {
        data->assets.GetLocalization(data->engine.language,"Police"),
        data->assets.GetLocalization(data->engine.language,"Secret Service"),
        data->assets.GetLocalization(data->engine.language,"Military")
    };
    data->gui.AddButtonBar("securityBar",texts,"vertical",secondaryBarPos,barSize,5);

    texts.clear();
    texts = {
        data->assets.GetLocalization(data->engine.language,"Organizations"),
        data->assets.GetLocalization(data->engine.language,"UN"),
        data->assets.GetLocalization(data->engine.language,"Aids")
    };
    data->gui.AddButtonBar("diplomacyBar",texts,"vertical",secondaryBarPos,barSize,5);

    texts.clear();
    texts = {
        data->assets.GetLocalization(data->engine.language,"State Budget"),
        data->assets.GetLocalization(data->engine.language,"Civil Servant"),
        data->assets.GetLocalization(data->engine.language,"Header of State"),
        data->assets.GetLocalization(data->engine.language,"Cabinet"),
        data->assets.GetLocalization(data->engine.language,"Parliament")
    };
    data->gui.AddButtonBar("governmentBar",texts,"vertical",secondaryBarPos,barSize,5);

    texts.clear();
    texts = {
        data->assets.GetLocalization(data->engine.language,"Population"),
        data->assets.GetLocalization(data->engine.language,"Health"),
        data->assets.GetLocalization(data->engine.language,"Education"),
        data->assets.GetLocalization(data->engine.language,"Work"),
        data->assets.GetLocalization(data->engine.language,"Housing")
    };
    data->gui.AddButtonBar("socialBar",texts,"vertical",secondaryBarPos,barSize,5);

    texts.clear();
    texts = {
        data->assets.GetLocalization(data->engine.language,"Media"),
        data->assets.GetLocalization(data->engine.language,"Culture"),
        data->assets.GetLocalization(data->engine.language,"Research"),
        data->assets.GetLocalization(data->engine.language,"Sports")
    };
    data->gui.AddButtonBar("investmentsBar",texts,"vertical",secondaryBarPos,barSize,5);
}

void SubMenusInit(GUIManager* baseGui,GUIManager* gui,AssetManager* asset,sf::RenderWindow* window,sf::Text* text,sf::RectangleShape* windowSprite, sf::RectangleShape* closeButton){
    baseGui->Reset();

    windowSprite->setFillColor(Color::grey);
    windowSprite->setOutlineThickness(5);
    windowSprite->setOutlineColor(Color::lightBlack);
    windowSprite->setSize(sf::Vector2f(window->getDefaultView().getSize().x*0.6,
                                       window->getDefaultView().getSize().y*0.8));
    windowSprite->setOrigin(windowSprite->getGlobalBounds().width/2,windowSprite->getGlobalBounds().height/2);
    windowSprite->setPosition(window->getDefaultView().getSize().x/2,window->getDefaultView().getSize().y/2);

    closeButton->setTexture(&asset->GetTexture("closeButton"),true);
    closeButton->setSize(sf::Vector2f(32,32));
    closeButton->setOrigin(closeButton->getSize().x/2,closeButton->getSize().y/2);
    closeButton->setPosition(windowSprite->getPosition().x+(windowSprite->getSize().x/2),
                             windowSprite->getPosition().y-(windowSprite->getSize().y/2));

    text->setFont(asset->GetFont("NotoSans"));
    text->setCharacterSize(35);
    text->setFillColor(Color::lightBlack);
    text->setOutlineThickness(2);
    text->setOutlineColor(Color::white);
    text->setOrigin(text->getGlobalBounds().width/2,text->getGlobalBounds().height/1.5);
    text->setPosition(windowSprite->getPosition().x,windowSprite->getPosition().y-(windowSprite->getSize().y/2)-40);
}

void SubMenusUpdate(GUIManager* baseGui,StateMachine* machine,InputManager* input,sf::RenderWindow* window,sf::View* view, sf::RectangleShape* windowSprite, sf::RectangleShape* closeButton){
    bool exit = false;

    if(input->IsSpriteClicked(closeButton->getGlobalBounds(),sf::Mouse::Left,*window,*view)){
        exit = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        exit = true;
    }

    if(exit){
        baseGui->Set("countryFlag","visible");
        baseGui->Set("playerFace","visible");
        baseGui->Set("gameDate","visible");
        baseGui->Set("stateName","visible");
        baseGui->Set("gameSpeed","visible");
        baseGui->Set("menuBar","visible");

        machine->RemoveState();
    }
}
