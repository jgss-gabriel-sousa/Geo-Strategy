#include "GUI/StateWindow.h"

UI::StateWindow::StateWindow(AssetManager* assetM,sf::Vector2f pos,sf::Vector2f Sizee,sf::RenderWindow* window){
    asset = assetM;
    position = pos;
    Size = Sizee;

    gui.Init(asset,window);
    gui.AddButton("terrain",position,{Size.x,Size.y/4},"","");
    gui.Set("terrain","texture=terrainGrassland");
}

void UI::StateWindow::Update(sf::RenderWindow* window,sf::View view){
    if(visible){
        gui.Update();
    }
}

void UI::StateWindow::Set(string argument){
    try{
        if(argument == "visible=false" || argument == "invisible"){
            visible = false;
        }
        else if(argument == "visible=true" || argument == "visible"){
            visible = true;
        }
    }
    catch(exception& e){
        Log::Push("Error in UI::StateWindow argument \""+argument+"\"");
    }
}

string UI::StateWindow::Return(string argument){
    ;
}

void UI::StateWindow::Draw(sf::RenderWindow* window){
    if(visible){
        gui.Draw();
        //window->draw(sprite);
    }
}





