#include "Engine/Engine.h"
#include "Engine/DEFINITIONS.h"
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include <locale>

int main(){
    srand(time(NULL));

    if(SHOW_CONSOLE == 0){
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    }

    try{
        Engine();
    }
    catch(std::exception& e){
        std::cout<<"An Exception as occurred: ";
        std::cout<< e.what()<<std::endl;
        Log::Write();
        return EXIT_FAILURE;
    }

    Log::Write();
    return EXIT_SUCCESS;
}
