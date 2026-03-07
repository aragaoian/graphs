#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<string>> lerGrafo(string path = "tests/ponderado.txt"){
    string text;
    ifstream file(path);
    vector<vector<string>> graphResult;

    if(file.is_open()){
        while(getline(file, text)){
            vector <string> info;
            for(char c: text){
                if(c == ' '){
                    continue;
                }
                info.push_back(string(1, c));
            }
            graphResult.push_back(info);
        }
        file.close();
    }else{
        cerr << "Não foi possível ler o arquivo" << endl;
    }

    return graphResult;
}

