#include "Engine/EntityManager.h"
#include "Engine/Engine.h"

class Event{
public:
    Event(){};
    virtual ~Event(){};

    void Create(string tit,vector<string> desc,vector<string> opt,string conditions,string trigger,Database* database);
    void Init(sf::Vector2f,sf::RenderWindow*,AssetManager*);
    void Draw(sf::RenderWindow*,sf::View* view);

    string title;
    vector<string> description;
    vector<string> options;
    sf::RectangleShape box;
    sf::RectangleShape picture;
    GUIManager gui;
};
