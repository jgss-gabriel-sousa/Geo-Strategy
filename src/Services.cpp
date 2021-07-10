#include "Services.h"

void Services::Update(Market* market,JobMarket* jobMarket,Country* country){
    eletricityNeeds = baseEletricityNeeds*qty;
    waterNeeds = baseWaterNeeds*qty;

    cost = 0;
    for(auto& kv : country->data.subsidies){
        if(kv.first == name){
            cost -= kv.second;
        }
    }

    employess = generalJobs+technicalJobs+expertJobs;
    maxEmployess = qty*baseGeneralJobs+qty*baseTechnicalJobs+qty*baseExpertJobs+1;

    double productsNecessary = 1;
    double productsReceived = 0;

    for(int i = 0; i<input.size(); i++){
        //pair<double,double> p = market->Buy(input[i].first,input[i].second*efficiency*qty*(employess/maxEmployess));
        pair<double,double> p = market->Buy(input[i].first,input[i].second*qty);
        cost += p.first;

        productsNecessary += (input[i].second*efficiency*qty*(employess/maxEmployess))*p.first;
        productsReceived += p.second*p.first;
    }
    productionEfficiency = productsReceived/productsNecessary;

    cost += generalJobs*(jobMarket->GetSalary("general"));
    cost += generalJobs*(jobMarket->GetSalary("technical"));
    cost += generalJobs*(jobMarket->GetSalary("expert"));

    if(cash < -500000)
        Dismantle(market,jobMarket);
    else if(cash > 500000 && balance > 0){
        int i = 0;
        //while(cash > 5 || i++ > 4){
            Build(market);
        //}
    }
    if(qty == 0){
        country->data.investmentFund += cash+balance+value;
        return;
    }

    Hire(jobMarket);

    value = (((employess*jobMarket->averageSalary)*6))+cash+(balance*12);
    balance = (demand*price)-cost;
    yearProfit += demand*price;
    cash -= balance;
    if(((cost/demand)*1.1) > price*1.2){ //Se o novo preço for muito diferente ele muda até uma certo limite
        price = price*1.2;
    }
    else if(((cost/demand)*1.1) > price*0.8){
        price = (cost/demand)*0.8;
    }
    market->SetPrice(tag,price);
    demand = 0;
    Log::Push("\n----------------------\n");
    Log::Push("\t"+name);
    Log::Push("   employess: "+to_string(generalJobs));
    Log::Push("maxEmployess: "+to_string(maxEmployess));
    Log::Push("salary avg: "+to_string(jobMarket->averageSalary));
    Log::Push("cash: "+to_string(cash));
    Log::Push("balance: "+to_string(balance));
    Log::Push(name+" value = "+to_string(value)+"M");
}

void Services::YearUpdate(){
    yearProfit = 0;
}

double Services::Request(double qty){
    demand += qty;
    cash += price*qty;
    return price*qty;
}

void Services::Hire(JobMarket* jobMarket){
    double gen = jobMarket->Request("general",(qty*baseGeneralJobs)-generalJobs);
    double tec = jobMarket->Request("technical",(qty*baseTechnicalJobs)-technicalJobs);
    double exp = jobMarket->Request("expert",(qty*baseExpertJobs)-expertJobs);

    generalJobs += gen;
    technicalJobs += tec;
    expertJobs += exp;
}

void Services::Build(Market* market){
    for(int i = 0; i<buildNeeds.size(); i++){
        balance += market->Buy(buildNeeds[i].first,input[i].second).first;
    }
    balance -= market->Buy("Construction",1).first;

    generalJobs += baseGeneralJobs;
    technicalJobs += baseTechnicalJobs;
    expertJobs += baseExpertJobs;

    qty++;
}

void Services::Dismantle(Market* market,JobMarket* jobMarket){
    for(int i = 0; i<buildNeeds.size(); i++){
        balance += market->Sell(buildNeeds[i].first,input[i].second*0.5);
    }

    double genFired = baseGeneralJobs;
    double tecFired = baseTechnicalJobs;
    double expFired = baseExpertJobs;

    if(generalJobs < baseGeneralJobs)
        genFired = generalJobs;
    if(technicalJobs < baseTechnicalJobs)
        tecFired = technicalJobs;
    if(expertJobs < baseExpertJobs)
        expFired = expertJobs;

    generalJobs -= genFired;
    technicalJobs -= tecFired;
    expertJobs -= expFired;

    balance -= jobMarket->Return("general",genFired);
    balance -= jobMarket->Return("technical",tecFired);
    balance -= jobMarket->Return("expert",expFired);

    qty--;
}
