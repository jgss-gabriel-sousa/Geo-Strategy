#include "Engine/Components.h"
#define PI 3.141592

void Bullet(Entity* entity,string argument){
    float speed = stod(argument);

    entity->SetVelocity(0,0);
    entity->SetVelocity(sin((PI/180)*entity->sprite.getRotation()) * speed,
                        cos((PI/180)*entity->sprite.getRotation()) * speed);
}
