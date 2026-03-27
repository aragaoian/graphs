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
        while(file >> text){
            graphResult.push_back(text);
        }

        file.close();

    }else{
        cerr << "Não foi possível ler o arquivo" << endl;
    }

    return graphResult;
}

