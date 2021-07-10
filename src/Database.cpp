#include "Database.h"

Database::Database(){
    gameDate.day = 1;
    gameDate.month = 1;
    gameDate.year = 2019;
    gameDate.total = 1;
}

void Database::AdvanceTime(){
    gameDate.day++;
    gameDate.total++;

    if(gameDate.day > 30){
        gameDate.day = 1;
        gameDate.month++;
    }
    if(gameDate.month > 12){
        gameDate.month = 1;
        gameDate.year++;
    }
}

float Database::CurrencyExchange(string c1,string c2){
    return currencies[c1].value / currencies[c2].value;
}

string Database::ValueToScale(double value,string returnScale,int decimalPlaces){
    if(returnScale == "thousand"){
        value /= 1000;
        returnScale = "K";
    }
    else if(returnScale == "million"){
        value /= 1000000;
        returnScale = "M";
    }
    else if(returnScale == "billion"){
        value /= 1000000000;
        returnScale = "B";
    }
    else if(returnScale == "trillion"){
        value /= 1000000000000;
        returnScale = "T";
    }
    else if(returnScale == "best"){
        returnScale = "";

        if(value > 999 && value < 1000000){
            value /= 1000;
            returnScale = "K";
        }
        else if(value > 999999 && value < 1000000000){
            value /= 1000000;
            returnScale = "M";
        }
        else if(value > 999999999 && value < 1000000000000){
            value /= 1000000000;
            returnScale = "B";
        }
        else if(value > 999999999999){
            value /= 1000000000000;
            returnScale = "T";
        }
    }

    //return SetPrecision(value,decimalPlaces)+" "+returnScale;
    return to_string(value)+" "+returnScale;
}

string Database::ValueToPercentage(double value,int decimalPlaces){
    string v = to_string(value);

    return v.substr(0,v.find(".")+decimalPlaces+1)+" %";
}

string Database::SetPrecision(double value,int decimalPlaces){
    string v = to_string(value);

    if(v.find(".") != string::npos)
        return v;
    else
        return v.substr(0,v.find(".")+decimalPlaces+1);
}

string Database::GetDate(string format){
    string date;
    string day = to_string(gameDate.day);
    string month = to_string(gameDate.month);
    string year = to_string(gameDate.year);

    if(month.size() == 1){
        month = "0"+month;
    }
    if(day.size() == 1){
        day = "0"+day;
    }

    if(format == "DMY" || format == "default")
        date = day+"/"+month+"/"+year;
    else if(format == "YMD")
        date = year+"/"+month+"/"+day;
    else if(format == "MDY")
        date = month+"/"+day+"/"+year;

    return date;
}
