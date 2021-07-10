#include "Market.h"

pair<double,double> Market::Buy(string product, double qtyToBuy){
    Product* p;
    double returnn;

    if(product == "")
        return make_pair(0,0);

    try{
        p = &market[product];
    }
    catch(exception& e){
        return make_pair(0,0);
    }

    if(qtyToBuy > p->qty){
        if(hierarchy == "national"){
            qtyToBuy = p->qty;

            pair<double,double> aux = globalMarket->Buy(product,qtyToBuy - p->qty);
            p->qty += aux.second;
            imports += aux.first;
        }else{
            ;
            //qtyToBuy = p->qty;
        }
    }

    returnn = qtyToBuy*p->price;
    p->qty -= qtyToBuy;


    if((p->price*((p->qty+qtyToBuy)/p->qty)) < p->price*0.8)
        p->price *= 0.8;
    else if((p->price*((p->qty+qtyToBuy)/p->qty)) > p->price*1.2)
        p->price *= 1.2;
    else
        p->price *= (p->qty+qtyToBuy)/p->qty;

    if(p->price < p->basePrice/4)
        p->price = p->basePrice/4;
    else if(p->price > p->basePrice*4){
        p->price = p->basePrice*4;
    }

    p->consumption += qtyToBuy;

    //Log::Push("Buy:"+product+" ("+to_string(qtyToBuy)+"): "+to_string(returnn/1000)+"M");
    return make_pair(returnn,qtyToBuy);
}

double Market::Sell(string product, double qtyToSell){
    Product* p;
    double returnn;

    if(product == "")
        return 0;

    try{
        p = &market[product];
    }
    catch(exception& e){
        return 0;
    }

    returnn = qtyToSell*p->price;


    if((p->price/((p->qty+qtyToSell)/p->qty)) < p->price*0.8)
        p->price *= 0.8;
    else if((p->price/((p->qty+qtyToSell)/p->qty)) > p->price*1.2)
        p->price *= 1.2;
    else
        p->price /= (p->qty+qtyToSell)/p->qty;

    if(p->price < p->basePrice/4)
        p->price = p->basePrice/4;
    else if(p->price > p->basePrice*4){
        p->price = p->basePrice*4;
    }

    p->qty += qtyToSell;
    p->production += qtyToSell;

    //Log::Push("Sell:"+product+" ("+to_string(qtyToSell)+"): "+to_string(returnn/1000)+"M");
    return returnn;
}

void Market::Update(){
    if(hierarchy == "national"){
        Product* p;
        for(auto& kv : market){
            p = &kv.second;

            if(p->consumption > p->production){
                pair<double,double> aux = globalMarket->Buy(p->tag,p->consumption-p->production);
                p->qty += aux.second;
                imports += aux.first;
            }
            if(p->consumption < p->production){
                double aux = globalMarket->Sell(p->tag,p->production-p->consumption);
                p->qty -= p->production-p->consumption;
                exports += aux;
            }

            //Log::Push(p->name+" = "+to_string(p->price));
        }
    }
}

void Market::YearUpdate(){
    imports = 0;
    exports = 0;

    Product* p;
    for(auto& kv : market){
        p = &kv.second;

        p->consumption = 0;
        p->production = 0;

        Log::Push(p->name+" = "+to_string(p->price));
    }

    system("pause");
}

double Market::GetPrice(string product){
    Product* p;

    if(product == "")
        return 0;

    try{
        p = &market[product];
    }
    catch(exception& e){
        return 0;
    }

    return p->price;
}


void Market::SetPrice(string product, double price){
    Product* p;

    if(product == "")
        return;

    try{
        p = &market[product];
    }
    catch(exception& e){
        return;
    }

    p->price = price;
}



