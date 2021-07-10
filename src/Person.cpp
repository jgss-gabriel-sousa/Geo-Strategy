#include "Person.h"

void Person::GenRandom(string country,AssetManager* asset){
    int aux;

    popularity = rand()%101;
    ideology = "";
    description = "";

    aux = 1+rand()%100;
    if(aux < 90){
        gender = "heterosexual";
    }
    else
        gender = "homosexual";


    aux = rand()%2;
    if(aux == 0){
        sex = "male";
    }
    else{
        sex = "female";
    }
/*
    sprite.body = asset->GetTexture(sex+"-body-"+to_string(1+rand()%BODY_QTY));
    sprite.eyes = asset->GetTexture(sex+"-eyes-"+to_string(1+rand()%EYES_QTY));
    sprite.face = asset->GetTexture(sex+"-face-"+to_string(1+rand()%FACE_QTY));
    sprite.hair = asset->GetTexture(sex+"-hair-"+to_string(1+rand()%HAIR_QTY));
    */
}
