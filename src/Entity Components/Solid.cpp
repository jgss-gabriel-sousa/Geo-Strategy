#include "Engine/Components.h"

void Solid(Entity* entity,string argument, vector<Entity*> entities){
    Entity* otherEntity;

    for(int i=0; i<entities.size(); i++){
        otherEntity = entities[i];

        if(otherEntity->GetId() == entity->GetId())
            continue;

        for(int j = 0; j<otherEntity->components.size(); j++){
            if(otherEntity->components[j].first == "solid"){
                if(otherEntity->sprite.getGlobalBounds().intersects(entity->sprite.getGlobalBounds())){
                    entity->SetVelocity(0,0);
                }
                continue;
            }
        }
    }
}
