#include "Engine/Components.h"

void Gravity(Entity* entity, string argument){
    float speed;

    try{
        speed = stod(argument);
    }
    catch(std::exception& e){
        Log::Push("exception in \"Gravity Component\" argument");
    }


    if(entity->GetVelocity().y < (entity->GetWidth()*entity->GetHeight()*entity->GetDrag())){
        entity->SetVelocity(entity->GetVelocity().x,entity->GetVelocity().y + speed);
    }
}
