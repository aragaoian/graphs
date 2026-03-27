#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "graphReader.h"

using namespace std;

vector<string> lerGrafo(string path = "tests/ponderado.txt"){
    string text;
    ifstream file(path);
    vector<string> graphResult;

    if(file.is_open()){
        while(getline(file, text)){
            vector<string> info;
            istringstream lineStream(text);
            string value;

            while(lineStream >> value){
                info.push_back(value);
            }

            if(info.empty()){
                continue;
            }

            graphResult.push_back(info);
        }
        file.close();
    }else{
        cerr << "Não foi possível ler o arquivo" << endl;
    }

    return graphResult;
}

