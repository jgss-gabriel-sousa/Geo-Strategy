#pragma once

#include <map>
#include <string>
#include <vector>
#include "Engine/Log.h"

using namespace std;

class JobMarket{
    /*
    struct Job{
        string tag;
        string name;
        unsigned int salary; //Base in 1
        unsigned long int workforce;
        double demand;
        double lastMonthDemand;
    };
    */

public:
    JobMarket(){};
    virtual ~JobMarket(){};

    double Request(string,double);
    double Return(string,double);
    double GetSalary(string);
    void Update(); //Monthly

    //void AddJobToMarket(string,string,unsigned int);

    //Name,Salary
    //vector<Job> jobs;
    double generalWorkforce=0;
    double generalSalary=0;
    double technicalWorkforce=0;
    double technicalSalary=0;
    double expertWorkforce=0;
    double expertSalary=0;

    double receivingUnemploymentBenefits=0; //Recebendo Auxílio Desemprego Estatal
    double minimumSalary=0;
    double averageSalary=0;
    double employerUnemploymentAssistance=0; //Assistência paga pelo empregador após a demissão
    double stateUnemploymentAssistance=0; //Assistência paga pelo estado após a demissão
};
