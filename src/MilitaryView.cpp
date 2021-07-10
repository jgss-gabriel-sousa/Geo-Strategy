#include "MilitaryView.h"

MilitaryView::MilitaryView(AssetManager* a,Database* d,EngineInfo*){
    asset = a;
    database = d;

    mouseCollider.setTexture(asset->GetTexture("point"));
}

void MilitaryView::Init(){
    asset->LoadTexture("tank",false);
    //asset->LoadTexture("tankIcon","textures/icons/units/tank.png");
    asset->LoadTexture("tankIcon",true);
    int separator = 0;
    for(int i = 0; i<10; i++){
        Units u;
        u.name = "tank";
        u.sprite.setPosition({2000+separator,500});
        u.sprite.setTexture(asset->GetTexture("tank"));
        u.sprite.setScale(0.05,0.05);
        //u.sprite.setScale(1,1);
        u.sprite.setOrigin(u.sprite.getGlobalBounds().width/2,u.sprite.getGlobalBounds().height/2);
        u.selection.setSize({u.sprite.getGlobalBounds().width*1.4,u.sprite.getGlobalBounds().height*1.4});
        u.selection.setFillColor(sf::Color(255,0,0,100));
        u.selection.setOrigin(u.selection.getGlobalBounds().width/2,u.selection.getGlobalBounds().height/2);
        u.icon.setTexture(asset->GetTexture("tankIcon"));
        u.icon.setOrigin(u.icon.getGlobalBounds().width/2,u.icon.getGlobalBounds().height/2);
        u.velocity = 0.1;
        u.posToMove = {-1000,-1000};
        separator += 1;
        units.push_back(u);
    }

    selectionBox.setFillColor(sf::Color(0,0,0,50));
}

void MilitaryView::UnitMovement(Units* unity){
    if(unity->posToMove.x == -1000)
        return;

    if(unity->posToMove.x < unity->sprite.getPosition().x){
        unity->sprite.setPosition({unity->sprite.getPosition().x-unity->velocity,unity->sprite.getPosition().y});
    }
    if(unity->posToMove.x > unity->sprite.getPosition().x){
        unity->sprite.setPosition({unity->sprite.getPosition().x+unity->velocity,unity->sprite.getPosition().y});
    }
    if(unity->posToMove.y < unity->sprite.getPosition().y){
        unity->sprite.setPosition({unity->sprite.getPosition().x,unity->sprite.getPosition().y-unity->velocity});
    }
    if(unity->posToMove.y > unity->sprite.getPosition().y){
        unity->sprite.setPosition({unity->sprite.getPosition().x,unity->sprite.getPosition().y+unity->velocity});
    }
}

void MilitaryView::Draw(sf::RenderWindow* window, sf::View* worldView, sf::View* guiView, InputManager* input){
    window->setView(*worldView);

    for(int i = 0; i<units.size(); i++){
        //Executa o Movimento da Unidade
        UnitMovement(&units[i]);

        //Se a caixa de seleção não estiver selecionado, o objeto não exibe a caixa de seleção interna
        if(!selection){
            units[i].selected = false;
        }

        //Verifica se esta dentro da tela, caso não esteja não é renderizado
        if(units[i].sprite.getPosition().x < worldView->getCenter().x-worldView->getSize().x/2){
            continue;
        }
        else if(units[i].sprite.getPosition().x > worldView->getCenter().x+worldView->getSize().x/2){
            continue;
        }
        else if(units[i].sprite.getPosition().y < worldView->getCenter().y-worldView->getSize().y/2){
            continue;
        }
        else if(units[i].sprite.getPosition().y > worldView->getCenter().y+worldView->getSize().y/2){
            continue;
        }

        //Se a caixa de seleção selecionar o objeto ele exibe a caixa de seleção interna
        if(input->BoxCollision(selectionBox.getGlobalBounds(),units[i].sprite.getGlobalBounds())){
            units[i].selected = true;
            selection = true;
        }

        units[i].selection.setPosition(units[i].sprite.getPosition());
        units[i].icon.setPosition(units[i].sprite.getPosition());

        //Renderiza o Objeto
        window->draw(units[i].sprite);
        if(units[i].selected){
            window->draw(units[i].selection);
        }
        if(worldView->getSize().x > 300){
            window->draw(units[i].icon);
        }
    }


    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && clicked == false){
        clicked = true;
        selection = false;
        basePos = input->GetMousePosition(*window, *worldView);
        selectionBox.setPosition(basePos);
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && clicked == true){
        clicked = false;
        selectionBox.setSize({0,0});
    }

    if(clicked){
        selectionBox.setSize({input->GetMousePosition(*window, *worldView).x-basePos.x,
                             input->GetMousePosition(*window, *worldView).y-basePos.y});
    }
    else{
        selectionBox.setPosition(input->GetMousePosition(*window, *worldView));
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && selection == true){
        clicked = false;
        selection = true;
        sf::Vector2f moveTo = input->GetMousePosition(*window, *worldView);
        //int aux;
        for(int i = 0; i<units.size(); i++){
            if(units[i].selected){
                //aux = rand()%2;
                units[i].posToMove = moveTo;
                //if(aux == 0)
                    moveTo.x += units[i].sprite.getGlobalBounds().width*1.2;
                //else
                    //moveTo.y += units[i].sprite.getGlobalBounds().height*1.2;
            }
        }
    }

    window->draw(selectionBox);
/*
    mouseCollider.setPosition(input->GetMousePosition(*window, *worldView));
    for(const auto& kv : database->states){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(Collision::PixelPerfectTest(mouseCollider,kv.second.sprite,0)){
                clickedState = &database->states[kv.first];

                window->draw(kv.second.text);
            }
        }
    }
*/
    window->setView(*guiView);
}
