#include "Engine/Components.h"

void SnapToGrid(Entity* entity, string argument){
    int distance = stoi(argument);
    int auxX = entity->GetX()/distance;
    int auxY = entity->GetY()/distance;

    entity->SetPosition(auxX*distance,auxY*distance);
}
