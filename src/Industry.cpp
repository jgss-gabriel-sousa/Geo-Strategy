#include "Industry.h"

void Industry::Update(Market* market,JobMarket* jobMarket,Country* country){
    eletricityNeeds = baseEletricityNeeds*qty;
    waterNeeds = baseWaterNeeds*qty;

    balance = 0;
    for(auto& kv : country->data.subsidies){
        if(kv.first == tag){
            balance = kv.second;
        }
    }

    employess = generalJobs+technicalJobs+expertJobs;
    maxEmployess = (qty*baseGeneralJobs)+(qty*baseTechnicalJobs)+(qty*baseExpertJobs)+1;
    double productsNecessary = 0.0000001;
    double productsReceived = 0;

    for(int i = 0; i<input.size(); i++){
        pair<double,double> p = market->Buy(input[i].first,input[i].second*efficiency*qty*(employess/maxEmployess));
        balance -= p.first;

        productsNecessary += (input[i].second*efficiency*qty*(employess/maxEmployess))*p.first;
        productsReceived += p.second*p.first;
    }
    productionEfficiency = productsReceived/productsNecessary;
    //double outputQty = (output.second * qty)*productionEfficiency;
    double outputQty = output.second * qty;
    double aux = market->Sell(output.first,outputQty);
    balance += aux;
    double profit = aux;

    balance -= generalJobs*(jobMarket->GetSalary("general"));
    balance -= technicalJobs*(jobMarket->GetSalary("technical"));
    balance -= expertJobs*(jobMarket->GetSalary("expert"));

    //Taxes
    aux = profit*(country->data.industryTax/100);
    balance = balance-aux;
    country->data.budget += aux;

    yearProfit += profit;

    if(cash < -1000000)
        Dismantle(market,jobMarket);
    else if(cash > 1000000 && balance > 0){
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

    value = (((employess*jobMarket->averageSalary)*6))+cash+(profit*6);
    Log::Push("\n----------------------\n");
    Log::Push("\t"+name+" - ("+country->data.name+") Industry");
    Log::Push("   employess: "+to_string(generalJobs));
    Log::Push("maxEmployess: "+to_string(maxEmployess));
    Log::Push("salary avg: "+to_string(jobMarket->averageSalary));
    Log::Push("cash: "+to_string(cash));
    Log::Push("profit: "+to_string(profit));
    Log::Push("balance: "+to_string(balance));
    Log::Push("taxes: "+to_string(aux));
    Log::Push(name+" value = "+to_string(value)+"M");
    cash += balance;
}

void Industry::YearUpdate(){
    yearProfit = 0;
}

void Industry::Hire(JobMarket* jobMarket){
    double gen = jobMarket->Request("general",(qty*baseGeneralJobs)-generalJobs);
    double tec = jobMarket->Request("technical",(qty*baseTechnicalJobs)-technicalJobs);
    double exp = jobMarket->Request("expert",(qty*baseExpertJobs)-expertJobs);

    generalJobs += gen;
    technicalJobs += tec;
    expertJobs += exp;
}

void Industry::Build(Market* market){
    for(int i = 0; i<buildNeeds.size(); i++){
        balance += market->Buy(buildNeeds[i].first,input[i].second).first;
    }
    balance -= market->Buy("Construction",1).first;

    generalJobs += baseGeneralJobs;
    technicalJobs += baseTechnicalJobs;
    expertJobs += baseExpertJobs;

    qty++;
}

void Industry::Dismantle(Market* market,JobMarket* jobMarket){
    int toDismantle = qty/4;
    if(toDismantle < 1)
        toDismantle = 1;
    if(toDismantle > qty)
        toDismantle = qty;

    for(int i = 0; i<buildNeeds.size(); i++){
        balance += toDismantle*market->Sell(buildNeeds[i].first,input[i].second*0.5*toDismantle);
    }

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
