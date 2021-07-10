#include "Engine/Components.h"

void Wrap(Entity* entity,string argument,sf::RenderWindow &window, sf::View worldView){
    if(entity->GetX() > worldView.getSize().x){
        entity->SetPosition(0,entity->GetY());
    }
    else if(entity->GetX() < 0){
        entity->SetPosition(worldView.getSize().x,entity->GetY());
    }
    else if(entity->GetY() > worldView.getSize().y){
        entity->SetPosition(entity->GetX(),0);
    }
    else if(entity->GetY() < 0){
        entity->SetPosition(entity->GetX(),worldView.getSize().y);
    }
}
