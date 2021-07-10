#pragma once

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DEFINITIONS.h"
#include "log.h"

using namespace std;

class AssetManager{
public:
    AssetManager();
    ~AssetManager(){}

    void LoadTexture(std::string name, std::string fileName);
    void LoadTexture(std::string name, std::string fileName, bool smooth);
    void LoadTexture(std::string name);
    void LoadTexture(std::string name, bool smooth);
    sf::Texture &GetTexture(std::string name);

    void LoadAnimation(std::string name, int frames);
    sf::Texture& GetAnimation(std::string name, int frame);
    int GetAnimationFrames(std::string name);

    void LoadFont(std::string name, std::string fileName);
    void LoadFont(std::string name);
    sf::Font &GetFont(std::string name);

    void LoadAudio(std::string name, std::string fileName);
    void LoadAudio(std::string name);
    sf::SoundBuffer &GetAudio(std::string name);
    void PlayAudio(std::string name);

    void SetLocalization(string language,string tag,string content);
    string GetLocalization(string language,string tag);

    bool CheckContent(string type, string name);
    bool CheckFile(string type, string filepath);

    sf::Sound songs;

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string,sf::Texture> animations;
    std::map<std::string,int> animationsFrames;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, sf::SoundBuffer> audios;
    map<string,map<string,string> > localizations;

    sf::Sound sound;
};
