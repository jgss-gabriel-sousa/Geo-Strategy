#include "SFML/Graphics.hpp"
#include "Engine/AssetManager.h"
#include "Engine/InputManager.h"
#include "Engine/Collision.h"
#include "Database.h"
#include "Engine/Engine.h"
#include <fstream>

using namespace std;

class MilitaryView{
public:
    MilitaryView(AssetManager*,Database*,EngineInfo*);
    virtual ~MilitaryView(){};

    void Init();
    void Draw(sf::RenderWindow*,sf::View*,sf::View*,InputManager*);

    void UnitMovement(Units*);

//private:
    AssetManager* asset;
    Database* database;
    EngineInfo* engineInfo;

    sf::Clock renderClock;

    vector<Units> units;
    sf::RectangleShape selectionBox;
    sf::Sprite mouseCollider;

    sf::Vector2f basePos;
    sf::Vector2f moveTo;
    bool clicked = false;
    bool selection = false;
};
