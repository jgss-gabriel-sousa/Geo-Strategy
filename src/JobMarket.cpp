#include "JobMarket.h"

double JobMarket::Request(string jobType, double qty){
    double* j;
    double* s;

    if(jobType == "general"){
        j = &generalWorkforce;
        s = &generalSalary;
    }
    else if(jobType == "technical"){
        j = &technicalWorkforce;
        s = &technicalSalary;
    }
    else if(jobType == "expert"){
        j = &expertWorkforce;
        s = &expertSalary;
    }

    if(qty > *j)
        qty = *j;

    //*s *=  (*j / (*j-qty)+1);
    *j -= qty;

    return qty;
}
/*
unsigned int JobMarket::Request(string jobType, unsigned int qty){
    Job* j;
    for(int i =0; i<jobs.size(); i++){
        if(jobs[i].tag == jobType){
            j = &jobs[i];
            break;
        }
    }

    if(qty > j->workforce)
        qty = j->workforce;

    j->demand += qty;

    j->workforce -= qty;

    return qty;
}

unsigned long int JobMarket::Return(string jobType, unsigned int qty){
    Job* j;
    for(int i =0; i<jobs.size(); i++){
        if(jobs[i].tag == jobType){
            j = &jobs[i];
            break;
        }
    }

    j->demand -= qty;
    j->workforce += qty;

    return (qty*employerUnemploymentAssistance)/1000000; //Mudando para base de Milhoes
}
*/

double JobMarket::Return(string jobType, double qty){
    double* j;
    double* s;

    if(jobType == "general"){
        j = &generalWorkforce;
        s = &generalSalary;
    }
    else if(jobType == "technical"){
        j = &technicalWorkforce;
        s = &technicalSalary;
    }
    else if(jobType == "expert"){
        j = &expertWorkforce;
        s = &expertSalary;
    }

    //*s *=  (*j / (*j+qty)+1);
    *j += qty;
    receivingUnemploymentBenefits += qty;

    return qty*employerUnemploymentAssistance; //Mudando para base de Milhoes
}

void JobMarket::Update(){
    /*peopleMoney += (receivingUnemploymentBenefits*stateUnemploymentAssistance)+
                    (receivingUnemploymentBenefits*employerUnemploymentAssistance);
    receivingUnemploymentBenefits = 0;*/

    averageSalary = ((generalSalary+technicalSalary+expertSalary)/3);
}


double JobMarket::GetSalary(string jobType){
    if(jobType == "general")
        return generalSalary;
    else if(jobType == "technical")
        return technicalSalary;
    else if(jobType == "expert")
        return expertSalary;
}

/*
void JobMarket::Update(double* peopleMoney){
    Job* j;
    for(int i = 0; i<jobs.size(); i++){
        j = &jobs[i];

        if(j->demand < 0){
            unsigned long int outgoing = rand()%j->workforce;
            int newJob;

            j->workforce -= outgoing;
            while(1){
                newJob = rand()%jobs.size();

                if(jobs[newJob].name == j->name && jobs.size() > 1)
                    continue;
                else{
                    jobs[newJob].workforce += outgoing;
                    break;
                }
            }
        }

        if(j->lastMonthDemand == 0)
            j->lastMonthDemand = 1;
        if(j->demand == 0)
            j->demand = 1;

        j->salary *= (j->demand/j->lastMonthDemand);
        if(j->salary < minimumSalary)
            j->salary = minimumSalary;

        j->lastMonthDemand = j->demand;
        j->demand = 0;

        *peopleMoney += j->receivingUnemploymentBenefits*stateUnemploymentAssistance;
        j->receivingUnemploymentBenefits = 0;
    }
}


void JobMarket::AddJobToMarket(string tag,string name,unsigned int salary){
    Job j;
    j.tag = tag;
    j.name = name;
    j.salary = salary;
    j.workforce = 0;
    j.demand = 1;
    j.lastMonthDemand = 1;
    j.receivingUnemploymentBenefits = 0;

    jobs.push_back(j);
}
*/
