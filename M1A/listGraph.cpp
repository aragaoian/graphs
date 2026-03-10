#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <graphCreator.h>
#include <graphReader.cpp>

using namespace std;


class GrafoList : public Grafo {
    private:
        unordered_map<int, vector<int>> grafo;

    public:
        bool criarGrafo(string path = "") override {
            if(path == "") return false;
            vector<vector<string>> info = lerGrafo();

            int casted_vertices = stoi(info[0][1]);
            int casted_arestas = stoi(info[0][1]);
            int casted_direcionado = stoi(info[0][1]);
            int casted_ponderado = stoi(info[0][1]);


            numVertices = casted_vertices;
            numArestas = casted_arestas;
            direcionado = true ? casted_direcionado == 1 : false;
            ponderado = true ? casted_ponderado == 1 : false;

            for(int i = 1; i < info.size(); i++){
                int vertice_origem = stoi(info[i][0]); 
                int vertice_destino = stoi(info[i][1]); 
                grafo[vertice_origem].push_back(vertice_destino);

                if(!direcionado){
                    grafo[vertice_destino].push_back(vertice_origem);
                }

                if(ponderado){
                    double peso = stod(info[i][2]);
                    // implementar
                }
            }

            return true;
        }

};