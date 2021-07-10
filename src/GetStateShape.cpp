#include "CountryState.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
}

// Loads as RGBA... even if file is only RGB
// Feel free to adjust this if you so please, by changing the 4 to a 0.
bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int&y)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 4);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y * 4);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

sf::Vector2f CountryState::GetStateShape(sf::Color color,int mapScale, string tag,AssetManager* assett){
    std::string filename = "resources/textures/provinces.bmp";
    vector<sf::Vector2f> points;

    int width, height;
    std::vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if(!success){
        cout<<"Error loading image\n";
        points.push_back(sf::Vector2f(-1,-1));
        return sf::Vector2f(0,0);
    }

    const size_t RGBA = 4;

    int r,g,b;
    sf::Vector2f pos;
    for(int y = 0, x = 0; y<height; x++){
        if(x > width){
            x = 0;
            y++;
        }
        if(y > height)
            break;

        size_t index = RGBA * (y * width + x);
        r = static_cast<int>(image[index + 0]);
        g = static_cast<int>(image[index + 1]);
        b = static_cast<int>(image[index + 2]);

        if(r == color.r && g == color.g && b == color.b){
            points.push_back(sf::Vector2f(x,y));
        }
    }

    //#######################################################

    sf::Vector2f smaller = sf::Vector2f(points[0].x,points[0].y);
    sf::Vector2f bigger = sf::Vector2f(points[0].x,points[0].y);

    for(int i = 1; i<points.size(); i++){
        if(points[i].x < smaller.x)
            smaller.x = points[i].x;
        if(points[i].y < smaller.y)
            smaller.y = points[i].y;

        if(points[i].x > bigger.x)
            bigger.x = points[i].x;
        if(points[i].y > bigger.y)
            bigger.y = points[i].y;
    }

    pos = sf::Vector2f(smaller.x,smaller.y);

    int w = bigger.x-smaller.x+1;
    int h = bigger.y-smaller.y+1;

    for(int i = 0; i<points.size(); i++){
        points[i] = sf::Vector2f(points[i].x-smaller.x,points[i].y-smaller.y);
    }

    sf::Image saveImage;
    saveImage.create(w,h,sf::Color(0,0,0,0));

    for(int i = 0; i<points.size(); i++){
        saveImage.setPixel(points[i].x,points[i].y,sf::Color(100,0,0,255));
    }

    saveImage.saveToFile("resources/textures/map/states/"+tag+".png");
    assett->LoadTexture(tag,"resources/textures/map/states/"+tag+".png");

    return pos;
}


void CountryState::SetProvinceColor(sf::Color newColor){
    std::string filename = "resources/textures/map/states/"+tag+".png";
    vector<sf::Vector2f> points;

    int width, height;
    std::vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if(!success){
        cout<<"Error loading image\n";
        points.push_back(sf::Vector2f(-1,-1));
        return;
    }

    const size_t RGBA = 4;

    int r,g,b;
    for(int y = 0, x = 0; y<height; x++){
        if(x > width){
            x = 0;
            y++;
        }
        if(y > height)
            break;

        size_t index = RGBA * (y * width + x);
        r = static_cast<int>(image[index + 0]);
        g = static_cast<int>(image[index + 1]);
        b = static_cast<int>(image[index + 2]);

        if(r == spriteColor.r && g == spriteColor.g && b == spriteColor.b){
            points.push_back(sf::Vector2f(x,y));
        }
    }

    //#######################################################

    if(points.size() == 0)
        Log::Push("error in "+name);
    if(points.size() != 0){
        sf::Vector2f smaller = sf::Vector2f(points[0].x,points[0].y);
        sf::Vector2f bigger = sf::Vector2f(points[0].x,points[0].y);

        for(int i = 1; i<points.size(); i++){
            if(points[i].x < smaller.x)
                smaller.x = points[i].x;
            if(points[i].y < smaller.y)
                smaller.y = points[i].y;

            if(points[i].x > bigger.x)
                bigger.x = points[i].x;
            if(points[i].y > bigger.y)
                bigger.y = points[i].y;
        }

        int w = bigger.x-smaller.x+1;
        int h = bigger.y-smaller.y+1;

        for(int i = 0; i<points.size(); i++){
            points[i] = sf::Vector2f(points[i].x-smaller.x,points[i].y-smaller.y);
        }

        sf::Image saveImage;
        saveImage.create(w,h,sf::Color(0,0,0,0));
        newColor.a = 150;

        for(int i = 0; i<points.size(); i++){
            saveImage.setPixel(points[i].x,points[i].y,newColor);
        }

        saveImage.saveToFile("resources/textures/map/states/"+tag+".png");
        asset->LoadTexture(name,"resources/textures/map/states/"+tag+".png");
    }
    sprite.setTexture(asset->GetTexture(tag));

    spriteColor = newColor;
}




