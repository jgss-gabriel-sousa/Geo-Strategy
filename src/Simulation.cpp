#include "Simulation.h"

Simulation::Simulation(Database* data){
    database = data;
}

void Simulation::Init(){
    ;
}

void Simulation::Update(){
    /*
    database->countryRanking.clear();

    Country* c;
    for(auto& kv : database->countries){
        c = &kv.second;
        database->countryRanking.push_back(make_pair(c->data.score,c->data.name));
        //system("pause");
    }

    sort(database->countryRanking.begin(),database->countryRanking.end(), greater<pair<double,string>>());

    for(int i = 0; i<database->countryRanking.size(); i++){
        CountrySimulation(&database->countries[database->countryRanking[i].second]);
    }
    */

    for(auto& kv : database->countries){
        CountrySimulation(&kv.second);
    }
}

void Simulation::CountrySimulation(Country* country){
    country->Update(database->GetDate("default"));

    if(country->ia){
        country->IASimulation();
    }
}










