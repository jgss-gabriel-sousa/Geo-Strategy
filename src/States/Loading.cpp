#include "States/Loading.h"
#include "States/GameMenu.h"

Loading::Loading(GameDataRef data) : data(data){
    ;
}

void Loading::Init(){
    data->engine.backgroundColor = Color::darkWhite;

    data->assets.LoadFont("NotoSans");

    data->gui.AddProgressBar("loading",loadingStage,LOADING_STAGES,
                             sf::Vector2f(data->engine.screenWidth/2,data->engine.screenHeight/2),
                             sf::Vector2f(data->engine.screenWidth*0.8,50),
                             "","loading",2);

    vector<string> files{"LoadingPhrases"};
    LoadLocalisation(files);
    data->gui.Set("loading","caption="+data->assets.GetLocalization(data->engine.language,"LOADING_PHRASE_"+
                                                                   to_string(1+rand()%PHRASES_COUNT)));
    data->gui.Set("loading","font=Arial");
}


void Loading::Update(float dt){
    data->gui.Set("loading","value="+to_string(loadingStage));

    if(phraseClock.getElapsedTime().asSeconds() > PHRASES_COUNTDOWN){
        phraseClock.restart();
        data->gui.Set("loading","caption="+data->assets.GetLocalization(data->engine.language,"LOADING_PHRASE_"+
                                                                       to_string(1+rand()%PHRASES_COUNT)));
    }


    if(loadingStage == 0 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        vector<string> files{"Interface","Countries","States","Cities"};
        LoadLocalisation(files);
        loadingStage++;
        delayClock.restart();
    }
    else if(loadingStage == 1 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        LoadFlags();
        loadingStage++;
        delayClock.restart();
    }
    else if(loadingStage == 2 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        LoadCurrencies();
        loadingStage++;
        delayClock.restart();
    }
    else if(loadingStage == 3 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        LoadEconomy();
        loadingStage++;
        delayClock.restart();
    }
    else if(loadingStage == 4 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        LoadCities();
        loadingStage++;
        delayClock.restart();
    }
    else if(loadingStage == 5 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        LoadStates();
        loadingStage++;
        delayClock.restart();
    }
    else if(loadingStage == 6 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        LoadCountries();
        loadingStage++;
        delayClock.restart();
    }
    else if(loadingStage == 7 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        //LoadParties();
        loadingStage++;
        delayClock.restart();
    }
    else if(loadingStage == 8 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        LoadSounds();
        loadingStage++;
        delayClock.restart();
    }
    else if(loadingStage == 9 && delayClock.getElapsedTime().asSeconds() > STAGES_DELAY){
        LoadOthers();
        loadingStage++;
        delayClock.restart();
    }

    if(loadingStagesNumberDebug){
        data->gui.Set("loading","caption="+to_string(loadingStage));
    }
    else if(stoi(data->gui.Get("loading","progress")) >= 100  && delayClock.getElapsedTime().asSeconds() > (STAGES_DELAY*3)){

        data->machine.AddState(StateRef(new GameMenu(this->data)),true);
    }
}


void Loading::LoadLocalisation(vector<string> files){
    string read, aux, tag;

    for(int i = 0; i<files.size(); i++){
        ifstream file;
        vector<string> language;
        vector<string> content;
        bool languagesDefined = false;
        string filename = "resources/localization/"+files[i]+".txt";

        file.open(filename,ios::in);

        if(file.is_open()){
            while(!file.eof() && !file.bad()){
                getline(file,read);

                if(read.find("//") != string::npos)
                    continue;
                if(read.size() == 0)
                    continue;

                if(languagesDefined){
                    content.clear();
                    aux = read.substr(read.find("=")+1);
                    tag = read.substr(0,read.find("="));

                    while(1){
                        if(aux.find("=") == string::npos){
                            content.push_back(aux);
                            languagesDefined = true;
                            break;
                        }

                        content.push_back(aux.substr(0,aux.find("=")));
                        aux = aux.substr(aux.find("=")+1);
                    }

                    for(int i = 0;i<language.size();i++){
                        data->assets.SetLocalization(language[i],tag,content[i]);
                        if(tag == "ENG"){
                            Log::Push(language[i]+"-"+tag+"-"+content[i]);
                        }
                    }
                }

                if(read.find("Languages:") != string::npos){
                    aux = read.substr(read.find(":")+1);
                    while(1){
                        if(aux.find(",") == string::npos){
                            language.push_back(aux);
                            languagesDefined = true;
                            break;
                        }

                        language.push_back(aux.substr(0,aux.find(",")));
                        aux = aux.substr(aux.find(",")+1);
                    }
                }
            }
        }
        else{
            Log::Push("Error in "+filename+" file: line="+read);
        }
    }
}


void Loading::LoadFlags(){
    string read, aux, tag;

    vector<string> tags;
    ifstream textFile;

    aux = "data/tags.txt";
    textFile.open(aux,ios::in);

    if(textFile.is_open()){
        while(!textFile.eof() && !textFile.bad()){
            getline(textFile,read);

            if(read.size() == 0)
                continue;
            if(read.find("//") != string::npos)
                continue;

            tags.push_back(read);
        }
    }
    else{
        Log::Push("Error in "+aux+" file: line="+read);
    }


    for(int i = 0; i<tags.size(); i++){
        ifstream file;
        vector<string> language;
        vector<string> content;
        bool languagesDefined = false;
        string filename = "resources/flags/"+tags[i]+".png";

        file.open(filename,ios::in);

        if(file.is_open()){
            while(!file.eof() && !file.bad()){
                getline(file,read);

                data->assets.LoadTexture(tags[i],"resources/flags/"+tags[i]+".png");
            }
        }
        else{
            Log::Push("Error in "+filename+" file: line="+read);
        }
    }
}


void Loading::LoadCurrencies(){
    string read, aux,name,manager,tag;
    float value;
    ifstream file;

    aux = "data/currencies.txt";
    file.open(aux,ios::in);

    if(file.is_open()){
        while(!file.eof() && !file.bad()){
            getline(file,read);

            if(read.size() == 0)
                continue;
            if(read.find("//") != string::npos)
                continue;

            tag = read.substr(0,read.find(":"));
            read = read.substr(read.find(":")+1);
            manager = read.substr(0,read.find("="));
            value = stod(read.substr(read.find("=")+1));

            name = data->assets.GetLocalization(data->engine.language,tag);

            data->database.currencies[tag] = Currency(name,tag,manager,value);
        }
    }
    else{
        Log::Push("Error in "+aux+" file: line="+read);
    }
}


void Loading::LoadCities(){
    /*
    string read, name, type;
    ifstream file;
    string filename = "data/cities.txt";
    double pop;
    sf::Vector2f position;

    file.open(filename,ios::in);

    if(file.is_open()){
        while(!file.eof() && !file.bad()){
            getline(file,read);
            Log::Push("Loading "+read.substr(0,read.find(";")));

            if(read.size() == 0)
                continue;
            if(read.find("//") != string::npos)
                continue;

            name = read.substr(0,read.find(";"));
            read = read.substr(read.find(";")+1);

            pop = stod(read.substr(0,read.find(";")));
            read = read.substr(read.find(";")+1);

            position.x = stoi(read.substr(0,read.find(",")));
            position.y = stoi(read.substr(read.find(",")+1));

            if(pop >= 1000000){
                type = data->assets.GetLocalization(data->engine.language,"metropolis");
            }
            else{
                type = data->assets.GetLocalization(data->engine.language,"bigCity");
            }

            data->database.cities[name] = City(data->assets.GetLocalization(data->engine.language,name),type,pop,position);
        }
    }
    else{
        Log::Push("Error in "+filename+" file: line="+read);
    }
    */
}

void Loading::LoadStates(){
    string read, aux;
    double pop;
    int area;
    vector<string> names;
    map<string,sf::Vector2f> positions;
    sf::Vector2f position;
    const int mapScale = 2;

    ifstream textFile;

    aux = "data/states.txt";
    textFile.open(aux,ios::in);

    if(textFile.is_open()){
        while(!textFile.eof() && !textFile.bad()){
            getline(textFile,read);

            if(read.size() == 0)
                continue;
            if(read.find("//") != string::npos)
                continue;

            names.push_back(read);
        }
    }
    else{
        Log::Push("Error in "+aux+" file: line="+read);
    }

    ifstream posFile;

    aux = "data/map/positions.txt";
    posFile.open(aux,ios::in);

    if(posFile.is_open()){
        while(!posFile.eof() && !posFile.bad()){
            getline(posFile,read);

            if(read.size() == 0)
                continue;
            if(read.find("//") != string::npos)
                continue;

            aux = read.substr(0,read.find("="));
            read = read.substr(read.find("=")+1);
            positions[aux] = sf::Vector2f(stoi(read.substr(0,read.find(","))),stoi(read.substr(read.find(",")+1)));
        }
    }
    else{
        Log::Push("Error in "+aux+" file: line="+read);
    }

    for(int i = 0; i<names.size(); i++){
        ifstream file;
        string filename = "data/states/"+names[i]+".txt";
        bool readingCities = false;
        bool readingNaturalResource = false;
        bool readingEconomy = false;
        sf::Color color = sf::Color(0,0,0,255);
        CountryState state;

        file.open(filename,ios::in);

        try{
        if(file.is_open()){
            while(!file.eof() && !file.bad()){
                getline(file,read);

                if(read.size() == 0)
                    continue;
                if(read.find("//") != string::npos)
                    continue;

                else if(read.find("population") != string::npos){
                    state.population = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("area") != string::npos){
                    state.area = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("color") != string::npos){
                    int r,g,b;

                    read = read.substr(read.find("=")+1);

                    r = stoi(read.substr(0,read.find(",")));
                    read = read.substr(read.find(",")+1);
                    g = stoi(read.substr(0,read.find(",")));
                    b = stoi(read.substr(read.find(",")+1));
                    color = sf::Color(r,g,b,255);
                }
                else if(read.find("cities") != string::npos){
                    readingCities = true;
                    continue;
                }
                else if(read.find("core") != string::npos){
                    read = read.substr(read.find("=")+1);
                    while(1){
                        if(read.find(",") == string::npos){
                            state.core.push_back(read);
                            break;
                        }

                        state.core.push_back(read.substr(0,read.find(",")));
                        read = read.substr(read.find(",")+1);
                    }
                }
                else if(read.find("claim") != string::npos){
                    read = read.substr(read.find("=")+1);
                    while(1){
                        if(read.find(",") == string::npos){
                            state.claim.push_back(read);
                            break;
                        }

                        state.claim.push_back(read.substr(0,read.find(",")));
                        read = read.substr(read.find(",")+1);
                    }

                    vector<string> added;
                    for(int i = 0; i<state.claim.size(); i++){
                        for(int j = 0; j<state.core.size(); j++){
                            if(state.claim[i] == state.core[j]){
                                added.push_back(state.core[j]);
                            }
                        }
                    }

                    bool ignore;
                    for(int i = 0; i<state.core.size(); i++){
                        ignore = false;

                        for(int j = 0; j<added.size(); j++){
                            if(added[j] == state.core[i]){
                                ignore = true;
                            }
                        }

                        if(!ignore)
                            state.claim.push_back(state.core[i]);
                    }
                }
                else if(read.find("naturalResource") != string::npos){
                    readingNaturalResource = true;
                    continue;
                }
                else if(read.find("economy") != string::npos){
                    readingEconomy = true;
                    continue;
                }

                if(readingCities){
                    if(read == "}"){
                        readingCities = false;
                        continue;
                    }

                    state.greatCities.push_back(&data->database.cities[read]);
                }
                if(readingNaturalResource){
                    if(read == "}"){
                        readingNaturalResource = false;
                        continue;
                    }

                    state.naturalResources.push_back(make_pair(read.substr(0,read.find("=")),stod(read.substr(read.find("=")+1))));
                }
                if(readingEconomy){
                    if(read == "}"){
                        readingEconomy = false;
                        continue;
                    }

                    string type = read.substr(read.find("(")+1,read.find(")")-1);
                    read = read.substr(read.find(")")+1);

                    if(type == "industry"){
                        Industry ind;
                        ind = data->database.industry[read.substr(0,read.find("="))];
                        ind.qty = stoi(read.substr(read.find("=")+1));

                        state.industries.push_back(ind);
                    }
                    else if(type == "agriculture"){
                        Agriculture agri;
                        agri = data->database.agriculture[read.substr(0,read.find("="))];
                        agri.qty = stoi(read.substr(read.find("=")+1));

                        if(agri.name == "")
                            continue;

                        state.agriculture.push_back(agri);
                    }
                    else if(type == "services"){
                        Services serv;
                        serv = data->database.services[read.substr(0,read.find("="))];
                        serv.qty = stoi(read.substr(read.find("=")+1));

                        state.services.push_back(serv);
                    }
                }
            }

            if(data->assets.CheckFile("texture", "resources/textures/map/states/"+names[i]+".png")){
                data->assets.LoadTexture(names[i],"resources/textures/map/states/"+names[i]+".png");

                auto found = positions.find(names[i]);

                if(found != positions.end()){
                    position = positions[names[i]];
                }
                else{
                    position = CountryState::GetStateShape(color,mapScale,names[i],&data->assets);
                    positions[names[i]] = position;
                }
            }
            else{
                position = CountryState::GetStateShape(color,mapScale,names[i],&data->assets);
            }

            if(position.x != -1000){
                state.name = data->assets.GetLocalization(data->engine.language,names[i]);
                state.tag = names[i];
                state.Init(position,&data->assets);
                data->database.states[names[i]] = state; //CountryState(names[i],aux,pop,cities,area,position,&data->assets,naturalResources,data->database.auxI);
            }
        }
        else{
            Log::Push("Error in "+filename+" file: line="+read);
        }
        }
        catch(exception& e){
            Log::Push("Error in "+names[i]+": line="+read);
        }
    }

    ofstream savePos;
    aux = "data/map/positions.txt";
    savePos.open(aux,ios::in);

    if(savePos.is_open()){
        for(const auto& kv : positions)
            //savePos<<"="<<endl;
            savePos<<kv.first<<"="<<kv.second.x<<","<<kv.second.y<<endl;
    }
    else{
        Log::Push("Error in "+aux+" file: line="+read);
    }
}

void Loading::LoadEconomy(){
    string read, name;
    Product product;

    ifstream file;
    file.open("data/economy/products.txt",ios::in);

    if(file.is_open()){
        while(!file.eof() && !file.bad()){
            getline(file,read);

            product.tag = read.substr(0,read.find("="));
            product.name = data->assets.GetLocalization(data->engine.language,product.tag);
            product.price = stod(read.substr(read.find("=")+1));
            product.basePrice = product.price;

            data->database.globalMarket.market[product.tag] = product;
        }
    }
    else{
        Log::Push("Error in data/economy/products.txt file");
    }

    Industry industry;
    Agriculture agriculture;
    Services services;

    bool readingBuildNeeds = false;
    bool readingInput = false;

    for(int i = 0; i<4; i++){
        ifstream file;
        if(i == 0)
            file.open("data/economy/industry.txt",ios::in);
        else if(i == 1)
            file.open("data/economy/agriculture.txt",ios::in);
        else if(i == 2)
            file.open("data/economy/services.txt",ios::in);
        else if(i == 3)
            file.open("data/economy/mining.txt",ios::in);

        if(file.is_open()){
            while(!file.eof() && !file.bad()){
                getline(file,read);

                if(read.size() == 0)
                    continue;
                if(read.find("//") != string::npos)
                    continue;

                if(i == 0){
                    if(read.find("buildNeeds") != string::npos){
                        readingBuildNeeds = true;
                        continue;
                    }
                    else if(read.find(";") != string::npos){
                        data->database.industry[name] = industry;
                        industry = Industry();
                        readingBuildNeeds = false;
                        readingInput = false;
                        continue;
                    }
                    else if(read.find("input") != string::npos){
                        readingInput = true;
                        continue;
                    }
                    else if(read.find("output") != string::npos){
                        industry.output = make_pair(read.substr(read.find("=")+1),1);
                    }
                    else if(read.find("category") != string::npos){
                        industry.category = read.substr(read.find("=")+1);
                    }
                    else if(read.find("generalJobs") != string::npos){
                        industry.baseGeneralJobs = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("technicalJobs") != string::npos){
                        industry.baseTechnicalJobs = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("expertJobs") != string::npos){
                        industry.baseExpertJobs = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("electricity") != string::npos){
                        industry.baseEletricityNeeds = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("water") != string::npos){
                        industry.baseWaterNeeds = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("{") != string::npos && !readingBuildNeeds && !readingInput){
                        name = read.substr(0,read.find("{"));
                        industry.name = data->assets.GetLocalization(data->engine.language,name);
                        industry.tag = name;
                        continue;
                    }

                    if(readingBuildNeeds){
                        if(read == "}"){
                            readingBuildNeeds = false;
                            continue;
                        }
                        industry.buildNeeds.push_back(make_pair(read.substr(0,read.find("=")),stod(read.substr(read.find("=")+1))));
                    }
                    if(readingInput){
                        if(read == "}"){
                            readingInput = false;
                            continue;
                        }
                        industry.input.push_back(make_pair(read.substr(0,read.find("=")),stod(read.substr(read.find("=")+1))));
                    }
                }
                if(i == 1){
                    if(read.find(";") != string::npos){
                        data->database.agriculture[name] = agriculture;
                        agriculture = Agriculture();
                        readingBuildNeeds = false;
                        readingInput = false;
                        continue;
                    }
                    else if(read.find("output") != string::npos){
                        agriculture.output = make_pair(name,stoi(read.substr(read.find("=")+1)));
                    }
                    else if(read.find("category") != string::npos){
                        agriculture.category = read.substr(read.find("=")+1);
                    }
                    else if(read.find("generalJobs") != string::npos){
                        agriculture.baseGeneralJobs = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("technicalJobs") != string::npos){
                        agriculture.baseTechnicalJobs = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("expertJobs") != string::npos){
                        agriculture.baseExpertJobs = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("electricity") != string::npos){
                        agriculture.baseEletricityNeeds = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("water") != string::npos){
                        agriculture.baseWaterNeeds = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("{") != string::npos){
                        name = read.substr(0,read.find("{"));
                        agriculture.name = data->assets.GetLocalization(data->engine.language,name);
                        agriculture.tag = name;
                        continue;
                    }
                }
                if(i == 2){
                    if(read.find("buildNeeds") != string::npos){
                        readingBuildNeeds = true;
                        continue;
                    }
                    else if(read.find(";") != string::npos){
                        data->database.services[name] = services;
                        services = Services();
                        readingBuildNeeds = false;
                        readingInput = false;
                        continue;
                    }
                    else if(read.find("input") != string::npos){
                        readingInput = true;
                        continue;
                    }
                    else if(read.find("output") != string::npos){
                        services.output = make_pair(read.substr(read.find("=")+1),1);
                    }
                    else if(read.find("category") != string::npos){
                        services.category = read.substr(read.find("=")+1);
                    }
                    else if(read.find("generalJobs") != string::npos){
                        services.baseGeneralJobs = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("technicalJobs") != string::npos){
                        services.baseTechnicalJobs = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("expertJobs") != string::npos){
                        services.baseExpertJobs = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("electricity") != string::npos){
                        services.baseEletricityNeeds = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("water") != string::npos){
                        services.baseWaterNeeds = stoi(read.substr(read.find("=")+1));
                    }
                    else if(read.find("{") != string::npos && !readingBuildNeeds && !readingInput){
                        name = read.substr(0,read.find("{"));
                        services.name = data->assets.GetLocalization(data->engine.language,name);
                        services.tag = name;
                        continue;
                    }

                    if(readingBuildNeeds){
                        if(read == "}"){
                            readingBuildNeeds = false;
                            continue;
                        }
                        services.buildNeeds.push_back(make_pair(read.substr(0,read.find("=")),stod(read.substr(read.find("=")+1))));
                    }
                    if(readingInput){
                        if(read == "}"){
                            readingInput = false;
                            continue;
                        }
                        services.input.push_back(make_pair(read.substr(0,read.find("=")),stod(read.substr(read.find("=")+1))));
                    }
                }
            }
        }
        else{
            Log::Push("Error in data/economy/ files");
        }
    }
}

void Loading::LoadSounds(){
    for(int i = 0; i < 10; i++)
        data->assets.LoadAudio("song ("+to_string(i)+")","resources/audios/songs/song ("+to_string(i)+").ogg");
}

void Loading::LoadOthers(){
    data->assets.LoadTexture("worldMapE",false);
    data->assets.LoadTexture("worldMapW",false);
    data->assets.LoadTexture("point");
    data->assets.LoadTexture("city");
    data->assets.LoadTexture("closeButton");
    data->assets.LoadTexture("pauseButton");
    data->assets.LoadTexture("speed1Button");
    data->assets.LoadTexture("speed2Button");
    data->assets.LoadTexture("speed3Button");

    //Put in a function
    data->assets.LoadTexture("terrainGrassland","resources/textures/map/terrain/grassland.png");
}


void Loading::LoadCountries(){
    string read, aux, tag;
    vector<string> names;
    ifstream textFile;

    aux = "data/tags.txt";
    textFile.open(aux,ios::in);

    if(textFile.is_open()){
        while(!textFile.eof() && !textFile.bad()){
            getline(textFile,read);

            if(read.size() == 0)
                continue;
            if(read.find("//") != string::npos)
                continue;

            names.push_back(read);
        }
    }
    else{
        Log::Push("Error in "+aux+" file");
    }

    for(int i = 0; i<names.size(); i++){
        Log::Push("Loading "+names[i]);
        ifstream file;
        string filename = "data/countries/"+names[i]+".txt";
        bool readingCulture = false;
        bool readingCongress = false;
        bool readingParties = false;
        bool readingDiplomacy = false;
        CountryDataPackage country;
        country.stateInterestRate = false;

        file.open(filename,ios::in);

        if(file.is_open()){
            while(!file.eof() && !file.bad()){
                getline(file,read);

                if(read.size() == 0)
                    continue;
                else if(read.find("//") != string::npos)
                    continue;
                else if(read.find("}") != string::npos)
                    continue;

                else if(read.find("Color") != string::npos){
                    read = read.substr(read.find("=")+1);
                    country.countryColor.r = stoi(read.substr(0,read.find(",")));
                    read = read.substr(read.find(",")+1);
                    country.countryColor.g = stoi(read.substr(0,read.find(",")));
                    read = read.substr(read.find(",")+1);
                    country.countryColor.b = stoi(read);
                }
                else if(read.find("CapitalState") != string::npos){
                    country.capitalState = &data->database.states[read.substr(read.find("=")+1)];
                }
                else if(read.find("Capital") != string::npos){
                    country.capital = &data->database.cities[read.substr(read.find("=")+1)];
                }
                else if(read.find("GovernmentType") != string::npos){
                    country.governmentType = read.substr(read.find("=")+1);
                }
                else if(read.find("States") != string::npos){
                    read = read.substr(read.find("=")+1);
                    while(1){
                        if(read.find(",") == string::npos){
                            country.states.push_back(&data->database.states[read]);

                            country.population = 0;
                            for(int i = 0; i< country.states.size();i++){
                                country.population += country.states[i]->population;
                            }

                            break;
                        }

                        country.states.push_back(&data->database.states[read.substr(0,read.find(","))]);
                        read = read.substr(read.find(",")+1);
                    }
                }
                else if(read.find("Culture") != string::npos){
                    readingCulture = true;
                    continue;
                }
                else if(read.find("GDPGrowthRate") != string::npos){
                    country.gdpGrowth = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("GDP") != string::npos){
                    country.gdp = stod(read.substr(read.find("=")+1));
                    country.gdp *= 1000000000;
                    country.investmentFund = country.gdp*0.1;
                }
                else if(read.find("BudgetRevenue") != string::npos){
                    country.budgetRevenue = stod(read.substr(read.find("=")+1));
                    country.budgetRevenue *= 1000000000;
                }
                else if(read.find("BudgetExpenditure") != string::npos){
                    country.budgetExpenditure = stod(read.substr(read.find("=")+1));
                    country.budgetExpenditure *= 1000000000;
                }
                else if(read.find("DebtRate") != string::npos){
                    float rate = stod(read.substr(read.find("=")+1));

                    if(rate >= 0){
                        country.debt = country.gdp*(rate/100);
                        country.stateCash = 0;
                    }
                    else{
                        country.debt = 0;
                        country.stateCash = country.gdp*((rate*-1)/100);
                    }
                }
                else if(read.find("InflationRate") != string::npos){
                    country.yearInflation = stod(read.substr(read.find("=")+1));
                    country.inflation = country.yearInflation;
                }
                else if(read.find("LaborForceRate") != string::npos){
                    country.laborForce = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("UnemploymentRate") != string::npos){
                    country.unemployment = stod(read.substr(read.find("=")+1));
                    double employment = country.population*(country.laborForce/100);
                    //employment *= country.unemployment/100;
                    country.jobMarket.generalWorkforce = employment*0.6;
                    country.jobMarket.technicalWorkforce = employment*0.3;
                    country.jobMarket.expertWorkforce = employment*0.1;
                    country.jobMarket.generalSalary = 320;
                    country.jobMarket.technicalSalary = 2000;
                    country.jobMarket.expertSalary = 4000;

                    country.richClass = country.jobMarket.expertWorkforce*6;
                    country.mediumClass = country.jobMarket.technicalWorkforce*6;
                    country.poorClass = country.population - country.mediumClass - country.richClass;
                }
                else if(read.find("MinimumWage") != string::npos){
                    country.jobMarket.minimumSalary = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Gini") != string::npos){
                    country.gini = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("Currency") != string::npos){
                    country.currency = &data->database.currencies[read.substr(read.find("=")+1)];
                }
                else if(read.find("CountryReserves") != string::npos){
                    country.countryReserves = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("InterestRate") != string::npos){
                    country.interestRate = stod(read.substr(read.find("=")+1));
                    country.stateInterestRate = true;
                }
                else if(read.find("Header of State") != string::npos){
                    country.headerOfState = read.substr(read.find("=")+1);
                }
                else if(read.find("HeaderTerm") != string::npos){
                    country.headerTerm = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("LastElection") != string::npos){
                    country.lastElection = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("SuffrageSystem") != string::npos){
                    country.suffrage = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("SuffrageAge") != string::npos){
                    country.suffrageAge = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("LegalSystem") != string::npos){
                    country.legalSystem = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("BroadcastMedia") != string::npos){
                    country.broadcastMedia = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Congress") != string::npos){
                    readingCongress = true;
                    continue;
                }
                else if(read.find("ChildrensRate") != string::npos){
                    country.childrens = country.population*(stod(read.substr(read.find("=")+1))/100);

                    for(int i = 0; i<country.states.size(); i++){
                        country.states[i]->childrens = (country.states[i]->population/country.population)*country.childrens;
                    }
                }
                else if(read.find("YoungRate") != string::npos){
                    country.young = country.population*(stod(read.substr(read.find("=")+1))/100);

                    for(int i = 0; i<country.states.size(); i++){
                        country.states[i]->young = (country.states[i]->population/country.population)*country.young;
                    }
                }
                else if(read.find("AdultRate") != string::npos){
                    country.adult = country.population*(stod(read.substr(read.find("=")+1))/100);

                    for(int i = 0; i<country.states.size(); i++){
                        country.states[i]->adult = (country.states[i]->population/country.population)*country.adult;
                    }
                }
                else if(read.find("OldRate") != string::npos){
                    country.old = country.population*(stod(read.substr(read.find("=")+1))/100);

                    for(int i = 0; i<country.states.size(); i++){
                        country.states[i]->old = (country.states[i]->population/country.population)*country.old;
                    }
                }
                else if(read.find("Birth") != string::npos){
                    double aux = stod(read.substr(read.find("=")+1));
                    country.birth = (aux*country.population)/1000;
                }
                else if(read.find("Death") != string::npos){
                    double aux = stod(read.substr(read.find("=")+1));
                    country.death = (aux*country.population)/1000;
                }
                else if(read.find("Migration") != string::npos){
                    double aux = stod(read.substr(read.find("=")+1));
                    country.migration = (aux*country.population)/1000;
                }
                else if(read.find("UrbanRate") != string::npos){
                    country.urban = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("LifeExpectancy") != string::npos){
                    country.lifeExpectancy = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("WaterRate") != string::npos){
                    country.water = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("Refugees") != string::npos){
                    country.refugees = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("PovertyRate") != string::npos){
                    country.poverty = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("HealthBudget") != string::npos){
                    country.healthBudget = country.gdp*(stod(read.substr(read.find("=")+1))/100);
                }
                else if(read.find("Doctors") != string::npos){
                    double aux = stod(read.substr(read.find("=")+1));
                    country.doctors = (aux*country.population)/1000;
                }
                else if(read.find("HospitalBed") != string::npos){
                    double aux = stod(read.substr(read.find("=")+1));
                    country.hospitalBed = (aux*country.population)/1000;
                }
                else if(read.find("EducationBudget") != string::npos){
                    country.educationBudget = country.gdp*(stod(read.substr(read.find("=")+1))/100);
                }
                else if(read.find("LiteracyRate") != string::npos){
                    country.literacy = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("SanitationRate") != string::npos){
                    country.literacy = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("EletricityRate") != string::npos){
                    country.eletricityRate = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("EletricityProduction") != string::npos){
                    country.eletricityProduction = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("EletricityConsumption") != string::npos){
                    country.eletricityConsumption = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("EletricityFossil") != string::npos){
                    country.eletricityFossil = stod(read.substr(read.find("=")+1));
                    country.fossilPowerPlant = (int)((country.eletricityProduction*(country.eletricityFossil/100))/0.003);
                }
                else if(read.find("EletricityNuclear") != string::npos){
                    country.eletricityNuclear = stod(read.substr(read.find("=")+1));
                    country.fossilPowerPlant = (int)((country.eletricityProduction*(country.eletricityNuclear/100))/0.01);
                }
                else if(read.find("EletricityHydroeletric") != string::npos){
                    country.eletricityHydroeletric = stod(read.substr(read.find("=")+1));
                    country.hydroelectricPlant = (int)((country.eletricityProduction*(country.eletricityHydroeletric/100))/2.00);
                }
                else if(read.find("EletricityRenewable") != string::npos){
                    country.eletricityRenewable = stod(read.substr(read.find("=")+1));
                    country.solarPowerPlant = (int)((country.eletricityProduction*(country.eletricityRenewable/100))/0.12)/2;
                    country.windPowerPlant = (int)((country.eletricityProduction*(country.eletricityRenewable/100))/0.12)/2;
                }
                else if(read.find("InternetRate") != string::npos){
                    country.internetRate = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("MobilePhoneRate") != string::npos){
                    country.mobilePhoneRate = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("Airports") != string::npos){
                    country.airports = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Roads") != string::npos){
                    country.roads = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Expressways") != string::npos){
                    country.expressways = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Railroads") != string::npos){
                    country.railroad = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("ElectrifiedRailroad") != string::npos){
                    country.electrifiedRailroad = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Ports") != string::npos){
                    country.ports = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("MillitaryBudget") != string::npos){
                    country.millitaryBudget = country.gdp*(stod(read.substr(read.find("=")+1))/100);
                }
                else if(read.find("MillitaryService") != string::npos){
                    country.millitaryService = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("MillitaryServiceAge") != string::npos){
                    country.millitaryServiceAge = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("ValueAddedTax") != string::npos){
                    country.valueAddedTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("CorporateTax") != string::npos){
                    country.corporateTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("ImportTax") != string::npos){
                    country.importTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("IncomeTax") != string::npos){
                    country.incomeTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("IndustryTax") != string::npos){
                    country.industryTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("ImportTax") != string::npos){
                    country.importTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("LargeFortunesTax") != string::npos){
                    country.largeFortunesTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("InheritanceTax") != string::npos){
                    country.inheritanceTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("VehicleRegistrationTax") != string::npos){
                    country.vehicleRegistrationTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("VehicleOwnershipTax") != string::npos){
                    country.vehicleOwnershipTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("PropertyTax") != string::npos){
                    country.propertyTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("AirlineTicketTax") != string::npos){
                    country.airlineTicketTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("AlcoholTax") != string::npos){
                    country.alcoholTax = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("ActivePersonnel") != string::npos){
                    country.activePersonnel = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("ReservePersonnel") != string::npos){
                    country.reservePersonnel = stod(read.substr(read.find("=")+1));
                }
                else if(read.find("Fighter") != string::npos){
                    country.fighter = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("AttackHelicopter") != string::npos){
                    country.attackHelicopter = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Tank") != string::npos){
                    country.tank = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("ArmoredVehicle") != string::npos){
                    country.armoredVehicle = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("SelfPropelledArtillery") != string::npos){
                    country.selfPropelledArtillery = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Artillery") != string::npos){
                    country.artillery = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("RocketProjector") != string::npos){
                    country.rocketProjector = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("AircraftCarrier") != string::npos){
                    country.aircraftCarrier = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Ships") != string::npos){
                    country.ships = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Submarines") != string::npos){
                    country.submarines = stoi(read.substr(read.find("=")+1));
                }
                else if(read.find("Diplomacy") != string::npos){
                     readingDiplomacy = true;
                     continue;
                }


                if(readingCulture == true){
                    if(read == "}")
                        readingCulture = false;

                    //culture.push_back(&data->database.cultures[read.substr(read.find("=")+1)]);
                }
                if(readingParties == true){
                    if(read == "}")
                        readingParties = false;

                    //culture.push_back(&data->database.cultures[read.substr(read.find("=")+1)]);
                }
                if(readingDiplomacy == true){
                    if(read == "}"){
                        readingDiplomacy = false;
                        continue;
                    }

                    country.diplomacy[read.substr(0,read.find("="))] = stoi(read.substr(read.find("=")+1));
                }
                if(readingCongress == true){
                    if(read == "}"){
                        readingDiplomacy = false;
                        continue;
                    }

                    if(read != "NONE"){
                        ;//country.parties.push_back(&data->database.parties[read.substr(0,read.find("=")+1)]);
                    }
                }
            }

            country.name = data->assets.GetLocalization(data->engine.language,names[i]);
            country.tag = names[i];

            data->database.countries[names[i]] = Country(country,&data->database.globalMarket);
        }
        else{
            Log::Push("Error in "+filename+" file: Line="+read);
        }
    }
}
