#include "Engine/Log.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace Log{
    std::vector<std::string> vectorLog;

    void Push(std::string text){
        std::cout<<text<<std::endl;
        vectorLog.push_back(text);
    }

    void Write(){
        std::ofstream file;
        std::string line;

        file.open("game.log");
        for(int i = 0; i < vectorLog.size(); ++i){
            file<<vectorLog[i]<<std::endl;
        }
        file.close();
    }
}
