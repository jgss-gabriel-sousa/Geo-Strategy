#include "Country.h"
#include "Engine/AssetManager.h"

Country::Country(CountryDataPackage d, Market* market){
    data = d;
    data.nationalMarket = *market;
    data.nationalMarket.hierarchy = "national";
    data.nationalMarket.globalMarket = market;

    text.setOutlineColor(sf::Color::Black);
    text.setString(data.name);

    int x,y,ssize = 1;
    data.population = 0;
    data.area = 0;
    for(int i = 0; i<data.states.size(); i++){
        ssize += data.states[i]->sprite.getGlobalBounds().width;

        data.states[i]->SetProvinceColor(data.countryColor);

        data.population += data.states[i]->population;
        data.area += data.states[i]->area;
    }

    x = data.capitalState->sprite.getPosition().x+data.capitalState->sprite.getGlobalBounds().width/2;
    y = data.capitalState->sprite.getPosition().y+data.capitalState->sprite.getGlobalBounds().height/2;

    text.setCharacterSize(ssize/8);
    if(text.getCharacterSize() > 50){
        text.setCharacterSize(ssize/16);
            if(text.getCharacterSize() > 50){
                text.setCharacterSize(50);
            }
    }
    if(text.getCharacterSize() < 10)
        text.setCharacterSize(10);

    text.setOutlineThickness(text.getCharacterSize()*0.1);
    text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
    text.setPosition(x,y);

    //Update("bootstrap");
    //FiscalYear();
    Product* p;
    int products = 0;
    for(auto& kv : data.nationalMarket.market){
        p = &kv.second;
        data.oldAvgPrice += p->price;
        products++;
    }
    data.oldAvgPrice /= products;

    lastYearData = data;
}


void Country::FiscalYear(){
    data.yearInflation = ((data.yearInflation/lastYearData.inflation)*100)-100;

    CountryState* cs;
    for(int i = 0; i<data.states.size(); i++){
        cs = data.states[i];
        for(int j = 0; j< cs->industries.size(); j++){
            data.industryGdp += cs->industries[j].yearProfit;
        }
        for(int j = 0; j< cs->agriculture.size(); j++){
            data.agricultureGdp += cs->agriculture[j].yearProfit;
        }
        for(int j = 0; j< cs->services.size(); j++){
            data.servicesGdp += cs->services[j].yearProfit;
        }
    }

    double aux = (data.exports - data.imports);
    if(aux < 0)
        aux = 0;

    data.gdp = data.industryGdp+data.agricultureGdp+data.servicesGdp+data.miningGdp+aux;
    data.gdp += data.budgetExpenditure+data.householdConsumption+data.investmentFundProfit;
    data.gdpGrowth = ((data.gdp/lastYearData.gdp)*100)-100;

    Log::Push("-------------------------------------------");
    Log::Push(data.name+" PIB = "+to_string(data.gdp)+" B");
    Log::Push("");
    Log::Push("industry: "+to_string(data.industryGdp));
    Log::Push("agriculture: "+to_string(data.agricultureGdp));
    Log::Push("services: "+to_string(data.servicesGdp));
    Log::Push("mining: "+to_string(data.miningGdp));
    Log::Push("exports: "+to_string(data.exports));
    Log::Push("imports: "+to_string(data.imports));
    Log::Push("budgetExpenditure: "+to_string(data.budgetExpenditure));
    Log::Push("householdConsumption: "+to_string(data.householdConsumption));
    Log::Push("investmentFundProfit: "+to_string(data.investmentFundProfit));
    Log::Push("-------------------------------------------");
    Log::Push("");


    //#####################################################################

    lastYearData = data;

    //#####################################################################
    //Reset
    data.industryGdp = 0;
    data.agricultureGdp = 0;
    data.miningGdp = 0;
    data.servicesGdp = 0;

    for(int i = 0; i<data.states.size(); i++){
        for(int j = 0; j< data.states[i]->industries.size(); j++){
            data.states[i]->industries[j].YearUpdate();
        }
        for(int j = 0; j< data.states[i]->services.size(); j++){
            data.states[i]->services[j].YearUpdate();
        }
        for(int j = 0; j< data.states[i]->agriculture.size(); j++){
            data.states[i]->agriculture[j].YearUpdate();
        }
        /*
        for(int j = 0; j< data.states[i]->mining.size(); j++){
            data.states[i]->mining[j].YearUpdate();
        }
        */
    }

    Log::Push("-------------------------------------------");
    Log::Push(data.name+" Market");
    Log::Push("");
    data.nationalMarket.YearUpdate();
    data.budgetRevenue = lastYearData.budget;
    data.budget = 0;
    data.budgetExpenditure = 0;
    data.stateCash = lastYearData.budgetRevenue-lastYearData.budgetExpenditure;
}


void Country::GDPPrevision(string date){
    string day = date.substr(0,date.find("/"));
    date = date.substr(date.find("/")+1);
    string month = date.substr(0,date.find("/"));
    date = date.substr(date.find("/")+1);
    string year = date;
    double total = 0;
    data.stockExchange = 0;
    double qty=0;

    CountryState* cs;
    for(int i = 0; i<data.states.size(); i++){
        cs = data.states[i];
        for(int j = 0; j< cs->industries.size(); j++){
            data.industryGdp += cs->industries[j].yearProfit;
            data.stockExchange += cs->industries[j].yearProfit;
            qty++;
        }
        for(int j = 0; j< cs->agriculture.size(); j++){
            data.agricultureGdp += cs->agriculture[j].yearProfit;
            data.stockExchange += cs->agriculture[j].yearProfit;
            qty++;
        }
        for(int j = 0; j< cs->services.size(); j++){
            data.servicesGdp += cs->services[j].yearProfit;
            data.stockExchange += cs->services[j].yearProfit;
            qty++;
        }
    }

    data.stockExchange /= qty;

    total = data.industryGdp+data.agricultureGdp+data.servicesGdp+data.miningGdp+data.exports-data.imports;
    total += data.budgetExpenditure+data.householdConsumption+data.investmentFundProfit;

    data.gdp = (total/stoi(month))*12;
    data.gdpGrowth = ((total/lastYearData.gdp)*100)-100;
}


void Country::Update(string date){
    string day,month,year;
    double stockQty=0;

    if(date != "bootstrap"){
        day = date.substr(0,date.find("/"));
        date = date.substr(date.find("/")+1);
        month = date.substr(0,date.find("/"));
        date = date.substr(date.find("/")+1);
        year = date;
    }

    //Industry,Services,Agriculture and Mining

    if(day == "01"){
        data.generalJobs = 0;
        data.technicalJobs = 0;
        data.expertJobs = 0;
    }

    if(day == "07"){
        for(int i = 0; i<data.states.size(); i++){
            for(int j = 0; j< data.states[i]->industries.size(); j++){
                data.states[i]->industries[j].Update(&data.nationalMarket,&data.jobMarket,this);
                if(data.states[i]->industries[j].qty == 0){
                    data.states[i]->industries.erase(data.states[i]->industries.begin()+j);
                }
                else{
                    data.generalJobs += data.states[i]->industries[j].generalJobs;
                    data.technicalJobs += data.states[i]->industries[j].technicalJobs;
                    data.expertJobs += data.states[i]->industries[j].expertJobs;
                }
            }
        }
    }
    if(day == "14"){
        for(int i = 0; i<data.states.size(); i++){
            for(int j = 0; j< data.states[i]->agriculture.size(); j++){
                data.states[i]->agriculture[j].Update(&data.nationalMarket,&data.jobMarket,this,i);
                if(data.states[i]->agriculture[j].qty == 0){
                    data.states[i]->agriculture.erase(data.states[i]->agriculture.begin()+j);
                }
                else{
                    data.generalJobs += data.states[i]->agriculture[j].generalJobs;
                    data.technicalJobs += data.states[i]->agriculture[j].technicalJobs;
                    data.expertJobs += data.states[i]->agriculture[j].expertJobs;
                }
            }
        }
    }
    if(day == "21"){
        for(int i = 0; i<data.states.size(); i++){
            for(int j = 0; j< data.states[i]->services.size(); j++){
                data.states[i]->services[j].Update(&data.nationalMarket,&data.jobMarket,this);
                if(data.states[i]->services[j].qty == 0){
                    data.states[i]->services.erase(data.states[i]->services.begin()+j);
                }
                else{
                    data.generalJobs += data.states[i]->services[j].generalJobs;
                    data.technicalJobs += data.states[i]->services[j].technicalJobs;
                    data.expertJobs += data.states[i]->services[j].expertJobs;
                }
            }
        }
    }
    /*
    if(day == "28"){
        for(int i = 0; i<data.mining.size(); i++){
            data.mining[i].Update(&data.nationalMarket,day,&data.jobMarket);
            employess += data.mining[i].employess;
        }
    }
    */

    data.nationalMarket.Update();

    //GDP and Stock Exchange
    if(day == "30"){
        GDPPrevision(day+"/"+month+"/"+year);
        if(data.stockExchangeVariation.size() == 30){
            data.stockExchangeVariation.erase(data.stockExchangeVariation.begin());
        }

        data.stockExchangeVariation.push_back(data.stockExchange);
    }

    //Trade Balance
    data.exports = data.nationalMarket.exports;
    data.imports = data.nationalMarket.imports;

    //Job Market
    if(day == "30" || date == "bootstrap"){
        data.jobMarket.Update();
    }

    //Unemployment
    //Log::Push(data.name+" jobs = "+to_string(employess));
    //data.unemployment = data.jobMarket.generalWorkforce + data.jobMarket.technicalWorkforce + data.jobMarket.expertWorkforce;
    //data.unemployment = (data.unemployment/lastYearData.population)*100;

    if(day == "30"){
        double employess = data.generalJobs+data.technicalJobs+data.expertJobs;
        data.unemployment = 100 - ((employess/((data.laborForce/100)*data.population))*100);
        data.unemploymentGrowth = ((data.unemployment/lastYearData.unemployment)*100)-100;
    }

    //Pop Update
    /*
    data.poorClassCash = data.generalJobs * data.jobMarket.generalSalary;
    data.mediumClassCash = data.technicalJobs * data.jobMarket.technicalSalary;
    data.richClassCash = data.expertJobs * data.jobMarket.expertSalary;
    data.poorClassMilitancy = 0;
    data.mediumClassMilitancy = 0;
    data.richClassMilitancy = 0;

        //Base Needs
        pair<double,double> result;
        //Poor
        result = data.nationalMarket.Buy("basicFoodBasket",data.poorClass);
        data.poorClassCash -= result.first;
        if(data.poorClass > result.second){
            data.poorClassMilitancy = (data.poorClass - result.second)/data.poorClass;
        }

        //Medium
        result = data.nationalMarket.Buy("basicFoodBasket",data.mediumClass*1.5);
        data.mediumClassCash -= result.first;
        if(data.mediumClass > result.second){
            data.mediumClassMilitancy = (data.mediumClass - result.second)/data.mediumClass;
        }

        //Rich
        result = data.nationalMarket.Buy("basicFoodBasket",data.richClass*2);
        data.richClassCash -= result.first;
        if(data.richClass > result.second){
            data.richClassMilitancy = (data.richClass - result.second)/data.richClass;
        }

        Log::Push(data.name);
        Log::Push("poor="+to_string(data.poorClass));
        Log::Push("militancy="+to_string(data.poorClassMilitancy));

        //Luxury Needs
        ;

        //Investments
        ;

        //Militancy
        ;

        //Immigration
        ;
    */

    //COUNTRY STATES UPDATE
    data.population = 0;
    data.area = 0;
    for(int i = 0; i<data.states.size(); i++){
        data.population += data.states[i]->population;
        data.area += data.states[i]->area;
    }


    //POP UPDATE
    if(day == "01" && month == "01" && start == false){
        double childrensAF,youngAF,adultAF,oldAF; //AF == advanceFactor
        double newPop=0;

        data.childrens = 0;
        data.young = 0;
        data.adult = 0;
        data.old = 0;

        for(int i = 0; i<data.states.size(); i++){
            childrensAF = data.states[i]->childrens/10;
            youngAF = data.states[i]->young/10;
            adultAF = data.states[i]->adult/45;
            oldAF = data.states[i]->old/(data.lifeExpectancy-65);

            data.states[i]->death = (data.states[i]->population/data.population)*data.death;
            data.states[i]->birth = (data.states[i]->population/data.population)*data.birth;
            data.states[i]->migration = (data.states[i]->population/data.population)*data.migration;

            if(oldAF < 0)
                oldAF = 0;

            data.states[i]->childrens = data.states[i]->childrens+data.states[i]->birth-childrensAF-(data.states[i]->death*0.1);
            data.states[i]->young = data.states[i]->young+childrensAF-youngAF-(data.states[i]->death*0.1);
            data.states[i]->adult = data.states[i]->adult+youngAF-adultAF-(data.states[i]->death*0.5)-data.states[i]->migration;
            data.states[i]->old = data.states[i]->old+adultAF-oldAF-(data.states[i]->death*0.3);

            if(data.states[i]->childrens < 0){
                data.states[i]->death += data.states[i]->childrens;
                data.states[i]->childrens = 0;
            }
            if(data.states[i]->young < 0){
                data.states[i]->death += data.states[i]->young;
                data.states[i]->young = 0;
            }
            if(data.states[i]->adult < 0){
                data.states[i]->death += data.states[i]->adult;
                data.states[i]->adult = 0;
            }
            if(data.states[i]->old < 0){
                data.states[i]->death += data.states[i]->old;
                data.states[i]->old = 0;
            }

            data.states[i]->population = data.states[i]->childrens+data.states[i]->young+data.states[i]->adult+data.states[i]->old;
            data.childrens += data.states[i]->childrens;
            data.young += data.states[i]->young;
            data.adult += data.states[i]->adult;
            data.old += data.states[i]->old;
            newPop += data.states[i]->population;
        }
        data.population = newPop;
    }


    //Inflation
    if(day == "30"){
        Product* p;
        double newAvgPrice = 0;
        int products = 0;
        for(auto& kv : data.nationalMarket.market){
            p = &kv.second;
            newAvgPrice += p->price;
            products++;
        }
        newAvgPrice /= products;
        data.inflation = ((newAvgPrice/data.oldAvgPrice)*100)-100;
        data.oldAvgPrice = newAvgPrice;
        if(data.inflationVariation.size() == 12){
            data.inflationVariation.erase(data.inflationVariation.begin());
        }
    }

    //Market auto correct Interest Rate
    if(!data.stateInterestRate){
        data.interestRate = data.inflation*1.05;
    }

    //Growth

    //IDH
    data.idh = 0;

    //Score
    data.score = data.millitaryBudget + data.gdp + data.idh;

    //New Year
    if(day == "01" && month == "01"){
        if(start){
            start = false;
        }
        else{
            FiscalYear();
        }
    }
}


void Country::IASimulation(){
    if(data.governmentType == "presidential republic"){
        ;
    }
}


