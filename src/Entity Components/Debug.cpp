#include "Engine/Components.h"

void Debug(Entity* entity,string argument){
    if(argument == "position"){
        Log::Push(entity->GetId()+": "+to_string((int)entity->GetX())+","+to_string((int)entity->GetY()));
    }
    else if(argument == "size"){
        Log::Push(entity->GetId()+": "+to_string((int)entity->GetWidth())+","+to_string((int)entity->GetHeight()));
    }
}
