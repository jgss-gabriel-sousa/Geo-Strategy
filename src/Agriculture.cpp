#include "Agriculture.h"

void Agriculture::Update(Market* market,JobMarket* jobMarket,Country* country,int stateId){
    eletricityNeeds = baseEletricityNeeds*qty;
    waterNeeds = baseWaterNeeds*qty;

    balance = 0;
    for(auto& kv : country->data.subsidies){
        if(kv.first == tag){
            balance = kv.second;
        }
    }

    employess = generalJobs+technicalJobs+expertJobs;
    maxEmployess = qty*baseGeneralJobs+qty*baseTechnicalJobs+qty*baseExpertJobs;

    //double production = output.second*efficiency*productionEfficiency*qty*(employess/maxEmployess);
    double production = output.second*qty;
    double maxProduction;

    pair<string,unsigned int>* resources;
    for(int i = 0; i<country->data.states[stateId]->naturalResources.size(); i++){
        if(country->data.states[stateId]->naturalResources[i].first == output.first){
            maxProduction = country->data.states[stateId]->naturalResources[i].second;
        }
    }

    if(production > maxProduction)
        production = maxProduction;

    double aux = market->Sell(output.first,production);

    yearProfit += aux;

    balance += aux;
    balance -= generalJobs*jobMarket->generalSalary;
    balance -= technicalJobs*jobMarket->technicalSalary;
    balance -= expertJobs*jobMarket->expertSalary;
    double wagesCost = aux-balance;

    if(cash < -500000)
        Dismantle(market,jobMarket);
    else if(cash > 500000){
        Build(market,aux,wagesCost);
    }
    if(qty == 0){
        country->data.investmentFund += cash+balance+value;
        return;
    }
    Hire(jobMarket);

    value = (((employess*jobMarket->averageSalary)*6))+cash+(aux*6);

    Log::Push("\n----------------------\n");
    Log::Push("\t"+name);
    Log::Push("         qty: "+to_string(qty));
    Log::Push("   employess: "+to_string(employess));
    Log::Push("maxEmployess: "+to_string(maxEmployess));
    Log::Push("salary cost: "+to_string(wagesCost));
    Log::Push("cash: "+to_string(cash));
    Log::Push("profit: "+to_string(aux));
    Log::Push("balance: "+to_string(balance));
    Log::Push(name+" value = "+to_string(value)+"M");

    cash += balance;
}

void Agriculture::YearUpdate(){
    yearProfit = 0;
}


void Agriculture::Hire(JobMarket* jobMarket){
    double gen = jobMarket->Request("general",(qty*baseGeneralJobs)-generalJobs);
    double tec = jobMarket->Request("technical",(qty*baseTechnicalJobs)-technicalJobs);
    double exp = jobMarket->Request("expert",(qty*baseExpertJobs)-expertJobs);

    generalJobs += gen;
    technicalJobs += tec;
    expertJobs += exp;
}

void Agriculture::Build(Market* market,double profit,double wagesCost){
    long long int toBuild = balance/((profit-wagesCost)/qty);

    generalJobs += baseGeneralJobs*toBuild;
    technicalJobs += baseTechnicalJobs*toBuild;
    expertJobs += baseExpertJobs*toBuild;

    qty += toBuild;
}

void Agriculture::Dismantle(Market* market,JobMarket* jobMarket){
   int toDismantle = qty/4;
    if(toDismantle < 1)
        toDismantle = 1;
    if(toDismantle > qty)
        toDismantle = qty;

    double genFired = baseGeneralJobs*toDismantle;
    double tecFired = baseTechnicalJobs*toDismantle;
    double expFired = baseExpertJobs*toDismantle;

    if(generalJobs < baseGeneralJobs*toDismantle)
        genFired = generalJobs;
    if(technicalJobs < baseTechnicalJobs*toDismantle)
        tecFired = technicalJobs;
    if(expertJobs < baseExpertJobs*toDismantle)
        expFired = expertJobs;

    generalJobs -= genFired;
    technicalJobs -= tecFired;
    expertJobs -= expFired;

    balance -= jobMarket->Return("general",genFired);
    balance -= jobMarket->Return("technical",tecFired);
    balance -= jobMarket->Return("expert",expFired);

    qty -= toDismantle;
}
