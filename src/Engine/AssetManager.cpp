#include "Engine/AssetManager.h"

AssetManager::AssetManager(){
    //Load standard items for errors when loading
    LoadTexture("missing");
    LoadFont("arial");
    LoadAudio("missing");
}

//################## TEXTURES #################################

void AssetManager::LoadTexture(std::string name, std::string fileName){
    sf::Texture tex;

    if(tex.loadFromFile(fileName)){
        //Log::Push("Texture Loaded to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\"");
    }else{
        tex.loadFromFile(MISSING_TEXTURE_FILEPATH);
        //Log::Push("Texture not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\" (Missing Texture applied)");
    }

    tex.setSmooth(true);
    this->textures[name] = tex;
}

void AssetManager::LoadTexture(std::string name, std::string fileName, bool smooth){
    sf::Texture tex;

    if(tex.loadFromFile(fileName)){
        //Log::Push("Texture Loaded to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\"");
    }else{
        tex.loadFromFile(MISSING_TEXTURE_FILEPATH);
        //Log::Push("Texture not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\" (Missing Texture applied)");
    }

    this->textures[name] = tex;
}

void AssetManager::LoadTexture(std::string name){
    sf::Texture tex;

    std::string filePath = TEXTURES_FOLDER_FILEPATH+name+".png";

    if(tex.loadFromFile(filePath)){
        //Log::Push("Texture Loaded to Asset Manager with tag: \""+name+"\" from: \""+filePath+"\"");
    }else{
        tex = textures.at("missing");
        //Log::Push("Texture not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+filePath+"\" (Missing Texture applied)");
    }

    tex.setSmooth(true);
    this->textures[name] = tex;
}

void AssetManager::LoadTexture(std::string name, bool smooth){
    sf::Texture tex;

    std::string filePath = TEXTURES_FOLDER_FILEPATH+name+".png";

    if(tex.loadFromFile(filePath)){
        //Log::Push("Texture Loaded to Asset Manager with tag: \""+name+"\" from: \""+filePath+"\"");
    }else{
        tex = textures.at("missing");
        //Log::Push("Texture not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+filePath+"\" (Missing Texture applied)");
    }

    this->textures[name] = tex;
}

sf::Texture& AssetManager::GetTexture(std::string name){
    auto found = textures.find(name);

    if(found != textures.end()){
        return this->textures.at(name);
    }else{
        return this->textures.at("Missing");
    }
}

//################## ANIMATIONS ####################################

void AssetManager::LoadAnimation(std::string name, int frames){
    sf::Texture tex;
    std::string filePath;
    std::string frameName;
    frames--;

    animationsFrames[name] = frames+1;

    for(int i = 0; i <= frames; i++){
        filePath = TEXTURES_FOLDER_FILEPATH+name+"/"+std::to_string(i)+".png";

        if(tex.loadFromFile(filePath)){
            Log::Push(filePath);
            Log::Push("Frame "+std::to_string(i)+" of "+std::to_string(frames)+" correctly loaded");
        }else{
            Log::Push("Frame "+std::to_string(i)+" of "+std::to_string(frames)+" error in loading");
            tex.loadFromFile(MISSING_TEXTURE_FILEPATH);
        }
        frameName = name+"-"+std::to_string(i);
        tex.setSmooth(true);
        animations[frameName] = tex;
    }
}

sf::Texture& AssetManager::GetAnimation(std::string name, int frame){
    name = name+"-"+std::to_string(frame);
    auto found = animations.find(name);

    if(found != animations.end()){
        return this->animations.at(name);
    }else{
        return this->textures.at("Missing");
    }
}

int AssetManager::GetAnimationFrames(std::string name){
    return animationsFrames[name];
}

//################## FONTS ####################################

void AssetManager::LoadFont(std::string name, std::string fileName){
    sf::Font font;

    if(font.loadFromFile(fileName)){
        Log::Push("Font Loaded to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\"");
        this->fonts[name] = font;
    }else{
        Log::Push("Font not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\" (Default Font (Arial) applied)");
        font.loadFromFile(FONT_ARIAL_FILEPATH);
        this->fonts[name] = font;
    }
}

void AssetManager::LoadFont(std::string name){
    sf::Font font;

    std::string filePath = FONTS_FOLDER_FILEPATH+name+".ttf";

    if(font.loadFromFile(filePath)){
        Log::Push("Font Loaded to Asset Manager with tag: \""+name+"\" from: \""+filePath+"\"");
        this->fonts[name] = font;
    }else{
        font.loadFromFile(FONT_ARIAL_FILEPATH);
        this->fonts[name] = font;
        Log::Push("Font not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+filePath+"\" (Default Font (Arial) applied)");
    }
}

sf::Font& AssetManager::GetFont(std::string name){
    auto found = fonts.find(name);

    if(found != fonts.end()){
        return this->fonts.at(name);
    }else{
        return this->fonts.at("arial");
    }
}

//################## AUDIO ####################################

void AssetManager::LoadAudio(std::string name, std::string fileName){
    sf::SoundBuffer sound;

    if(sound.loadFromFile(fileName)){
        this->audios[name] = sound;
        Log::Push("Audio Loaded to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\"");
    }else{
        Log::Push("Audio not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\" (Missing Audio applied)");
        sound.loadFromFile(MISSING_AUDIO_FILEPATH);
        this->audios[name] = sound;
    }
}

void AssetManager::LoadAudio(std::string name){
    sf::SoundBuffer sound;

    std::string filePath = AUDIO_FOLDER_FILEPATH+name+".wav";

    if(sound.loadFromFile(filePath)){
        Log::Push("Audio Loaded to Asset Manager with tag: \""+name+"\" from: \""+filePath+"\"");
    }else{
        sound.loadFromFile(MISSING_AUDIO_FILEPATH);
        Log::Push("Audio not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+filePath+"\" (Missing Audio applied)");
    }
    this->audios[name] = sound;
}

sf::SoundBuffer& AssetManager::GetAudio(std::string name){
    auto found = audios.find(name);

    if(found != audios.end()){
        return this->audios.at(name);
    }else{
        return this->audios.at("missing");
    }
}

void AssetManager::PlayAudio(std::string name){
    sound.setBuffer(GetAudio(name));
    sound.play();
}


//################## LOCALIZATION ####################################

void AssetManager::SetLocalization(string language,string tag,string content){
    localizations[language][tag] = content;
}

string AssetManager::GetLocalization(string language,string tag){
    auto found1 = localizations.find(language);

    if(found1 != localizations.end()){
        auto found2 = localizations[language].find(tag);

        if(found2 != localizations[language].end()){
            return localizations[language][tag];
        }else{
            return tag;
        }
    }else{
        return tag;
    }

    return localizations[language][tag];
}


//################## OTHERS ####################################

bool AssetManager::CheckContent(string type, string name){
    if(type == "texture"){
        auto found = textures.find(name);

        if(found != textures.end())
            return true;
        else
            return false;
    }

    return false;
}

bool AssetManager::CheckFile(string type, string filepath){
    if(type == "texture"){
        sf::Texture tex;
        if(tex.loadFromFile(filepath))
            return true;
        else
            return false;
    }

    return false;
}

