#include "Engine/EntityManager.h"

EntityManager::EntityManager(){
    //ctor
}

void EntityManager::AddEntity(Entity* entity){
    entities.push_back(entity);
}

void EntityManager::Update(sf::RenderWindow &window,sf::View worldView){
    string component,argument;

    for(int i = 0; i<entities.size(); i++){
        //Update Position
        entities[i]->SetPosition(entities[i]->GetX()+entities[i]->GetVelocity().x,
                                 entities[i]->GetY()+entities[i]->GetVelocity().y);

        entities[i]->SetVelocity((int)(entities[i]->GetVelocity().x/2),
                                 (int)(entities[i]->GetVelocity().y/2));

        //Update Components
        for(int j = 0; j<entities[i]->components.size(); j++){
            component = entities[i]->components[j].first;
            argument = entities[i]->components[j].second;

            if(component == "gravity"){
                Gravity(entities[i],argument);
            }
            else if(component == "draggable"){
                Draggable(entities[i],argument,window,worldView);
            }
            else if(component == "bullet"){
                Bullet(entities[i],argument);
            }
            else if(component == "debug"){
                Debug(entities[i],argument);
            }
            else if(component == "wrap"){
                Wrap(entities[i],argument,window,worldView);
            }
            else if(component == "rotate"){
                Rotate(entities[i],argument);
            }
            else if(component == "movement"){
                Movement(entities[i],argument);
            }
            else if(component == "snapToGrid"){
                SnapToGrid(entities[i],argument);
            }
            else if(component == "solid"){
                Solid(entities[i],argument,entities);
            }
        }

        //Draw
        window.draw(entities[i]->sprite);
    }
}
