#include "SFML/Graphics.hpp"
#include "Engine/AssetManager.h"
#include "Engine/InputManager.h"
#include "Engine/Collision.h"
#include "Database.h"
#include <fstream>

using namespace std;

//Trasnferir classe para incicialização durante o loading
class WorldMap{
public:
    WorldMap(AssetManager*,Database*);
    virtual ~WorldMap(){};

    void Init();
    void Draw(sf::RenderWindow*,sf::View*,sf::View*,InputManager*,string*);

//private:
    AssetManager* asset;
    Database* database;

    sf::Sprite backgroundE;
    sf::Sprite backgroundW;
    sf::Sprite fakeRoundW;
    sf::Sprite fakeRoundE;
    sf::RectangleShape waterPlaces;
    sf::Sprite mouseCollider;
};
