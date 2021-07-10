#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

vector<string> originalFile;

int main(){
    ifstream input;
    input.open("coal.txt",ios::in)
    if(file.is_open()){
        while(!file.eof() && !file.bad()){
            getline(file,read);

            originalFile.push_back(read);
        }
    }
    else{
        Log::Push("Error in input file");
    }

    ofstream file;
    file.open("save.txt",ios::out);

    if(file.is_open()){
        for(int i = 0; i<originalFile.size(); i++){
            file<<originalFile[i]<<std::endl;
        }
    }

    return 0;
}
