#include "Engine/Engine.h"
#include "States/SplashState.h"

Engine::Engine(){
    UserConfigs();

    actualResolution = sf::Vector2f(data->window.getDefaultView().getSize().x,data->window.getDefaultView().getSize().y);
    data->engine.backgroundColor = Color::black;
    data->engine.worldView.setSize(actualResolution.x,actualResolution.y);

    data->window.setVerticalSyncEnabled(true);
    data->machine.AddState(StateRef(new SplashState(this->data)));

    sf::Image icon;
    icon.loadFromFile("resources/textures/icon.png");
    data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    data->gui.Init(&data->assets,&data->window);

    this->Run();
}

void Engine::UserConfigs(){
    int width = actualResolution.x, height = actualResolution.y;
    bool fullscreen = false;
    ifstream file;
    string read;

    file.open(USER_CONFIG_FILE,ios::in);

    if(file.is_open()){
        while(!file.eof() && !file.bad()){
            getline(file,read);

            try{
                if(read.find("resolution") != string::npos){
                    read = read.substr(read.find("=")+1);
                    width = stoi(read.substr(0,read.find("x")));
                    height = stoi(read.substr(read.find("x")+1));
                }
                else if(read.find("fullscreen") != string::npos){
                    read = read.substr(read.find("=")+1);
                    if(read == "true")
                        fullscreen = true;
                }
                else if(read.find("language") != string::npos){
                    read = read.substr(read.find("=")+1);
                    data->engine.language = read;
                }
                else if(read.find("dataFormat") != string::npos){
                    read = read.substr(read.find("=")+1);
                    data->engine.dataFormat = read;
                }
            }
            catch(exception& e){
                string aux = USER_CONFIG_FILE;
                Log::Push("Error in \""+aux+"\" file");
            }
        }
    }


    if(width == 0 || height == 0){
        width = START_SCREEN_WIDTH;
        height = START_SCREEN_HEIGHT;
        actualResolution = sf::Vector2f(START_SCREEN_WIDTH,START_SCREEN_HEIGHT);
    }

    if(fullscreen)
        data->window.create(sf::VideoMode(width,height),"",sf::Style::Fullscreen);
    else
        data->window.create(sf::VideoMode(width,height),"",sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar);
}

void Engine::CheckFocus(){
    if(!data->window.hasFocus()){
        data->window.setFramerateLimit(10);
    }
    else{
        data->window.setFramerateLimit(framerate);
    }
}

void Engine::UpdateAndDrawEntities(){
    data->entities.Update(data->window,data->engine.worldView);
}

void Engine::UpdateUI(){
    data->gui.Update();
}

void Engine::DrawUI(){
    data->gui.Draw();
}

void Engine::GlobalWindowEvents(){
    data->engine.GUIview = data->window.getDefaultView();


    while(data->window.pollEvent(data->engine.event)){
        if(sf::Event::Closed == data->engine.event.type){
            this->data->window.close();
        }
        if(data->engine.event.type == sf::Event::Resized){
            data->engine.GUIview.setSize({
                static_cast<float>(data->engine.event.size.width),
                static_cast<float>(data->engine.event.size.height)
            });

            actualResolution = sf::Vector2f(data->engine.GUIview.getSize().x,data->engine.GUIview.getSize().y);

            data->window.setView(data->engine.GUIview);
        }
        if(data->engine.event.type == sf::Event::MouseWheelScrolled){
            if(data->engine.event.mouseWheelScroll.delta < 0){
                data->engine.worldView.zoom(1.10);
            }
            if(data->engine.event.mouseWheelScroll.delta > 0){
                data->engine.worldView.zoom(0.90);
            }
        }
    }
}

void Engine::UpdateEngineInfo(float frameTime){
    data->engine.screenWidth = actualResolution.x;
    data->engine.screenHeight = actualResolution.y;

    if(frameTime != 0)
        data->engine.fps = 1/frameTime;
    else
        data->engine.fps = 0;
}

void Engine::Run(){
    float newTime, frameTime, interpolation;

    float currentTime = gameClock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while(data->window.isOpen()){
        CheckFocus();
        GlobalWindowEvents();
        UpdateEngineInfo(frameTime);

        data->machine.ProcessStateChanges();

        newTime = gameClock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if(frameTime > 0.25f)
            frameTime = 0.25f;


        currentTime = newTime;
        accumulator += frameTime;

        while(accumulator >= dt){
            data->machine.GetActiveState()->HandleInput();

            //if(tickRate)
                data->machine.GetActiveState()->Update(dt);

            data->gui.Update();

            accumulator -= dt;
        }
        interpolation = accumulator / dt;
        data->window.clear(data->engine.backgroundColor);
        data->machine.GetActiveState()->Draw(interpolation);

        data->window.setView(data->engine.worldView);
        UpdateAndDrawEntities();
        data->window.setView(data->engine.GUIview);
        DrawUI();
        data->window.display();
    }
}
