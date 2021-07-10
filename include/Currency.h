#pragma once

class Currency{
public:
    Currency(){}
    Currency(string n,string t,string m,float v){
        name = n;
        tag = t;
        manager = m;
        value = v;
    };
    ~Currency(){};

    string name;
    string tag;
    string manager;
    float value; //in gold
};
