#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include "matrixGraph.h"
#include "graphReader.h"

using namespace std;

int GrafoMatriz::indexMaximo(){
    return static_cast<int>(grafo.size()) - 1;
}

bool GrafoMatriz::criarGrafo(string path){
    if(path == "") return false;
    vector<string> info = lerGrafo(path);
    if(info.size() < 4) return false;
    if((info.size() - 4) % 3 != 0) return false;

    int casted_vertices = stoi(info[0]);
    int casted_direcionado = stoi(info[2]);
    int casted_ponderado = stoi(info[3]);

    numVertices = casted_vertices;
    numArestas = 0;
    direcionado = (casted_direcionado == 1);
    ponderado = (casted_ponderado == 1);

    grafo.assign(numVertices, vector<float>(numVertices, -1.0f));
    labels.clear();

    for(int i = 4; i < info.size() - 2; i += 3){
        int vertice_origem = stoi(info[i]);
        int vertice_destino = stoi(info[i + 1]);
        if(vertice_origem < 0 || vertice_origem >= numVertices || vertice_destino < 0 || vertice_destino >= numVertices){
            return false;
        }

        float peso = ponderado ? stof(info[i + 2]) : 1.0f;
        if(!inserirAresta(vertice_origem, vertice_destino, peso)){
            return false;
        }
    }

    return true;
}

bool GrafoMatriz::inserirVertice(string label){
    try{
        int novoTamanho = numVertices + 1;

        for(auto& linha: grafo){
            linha.push_back(-1.0f);
        }

        grafo.push_back(vector<float>(novoTamanho, -1.0f));

        if(label != ""){
            labels[numVertices] = label;
        }

        numVertices++;
        return true;
    }catch(const runtime_error& e){
        return false;
    }
}

bool GrafoMatriz::removerVertice(int indice){
    if(indice < 0 || indice >= numVertices){
        return false;
    }

    grafo.erase(grafo.begin() + indice);
    for(auto& linha: grafo){
        linha.erase(linha.begin() + indice);
    }

    // Recompute edge count from matrix to keep it consistent after index shifting.
    numArestas = 0;
    for(int i = 0; i < static_cast<int>(grafo.size()); i++){
        for(int j = 0; j < static_cast<int>(grafo[i].size()); j++){
            if(grafo[i][j] == -1.0f){
                continue;
            }

            if(direcionado || i <= j){
                numArestas++;
            }
        }
    }

    map<int, string> novosLabels;
    for(const auto& pair: labels){
        if(pair.first < indice){
            novosLabels[pair.first] = pair.second;
        }else if(pair.first > indice){
            novosLabels[pair.first - 1] = pair.second;
        }
    }

    labels = novosLabels;
    numVertices--;
    return true;
}

string GrafoMatriz::labelVertice(int indice){
    auto it = labels.find(indice);
    return it == labels.end() ? "Vertice nao possui label." : it->second;
}

vector<int> GrafoMatriz::retornarVertices(){
    vector<int> vertices;
    for(int i = 0; i < numVertices; i++){
        vertices.push_back(i);
    }
    return vertices;
}

vector<int> GrafoMatriz::retornarVizinhos(int vertice){
    vector<int> vizinhos;
    if(vertice < 0 || vertice >= numVertices){
        return vizinhos;
    }

    for(int i = 0; i < grafo[vertice].size(); i++){
        if(grafo[vertice][i] != -1.0f){
            vizinhos.push_back(i);
        }
    }

    return vizinhos;
}

bool GrafoMatriz::inserirAresta(int origem, int destino, float peso){
    if(origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices){
        return false;
    }

    float pesoFinal = ponderado ? peso : 1.0f;
    bool arestaNova = grafo[origem][destino] == -1.0f;

    grafo[origem][destino] = pesoFinal;
    if(!direcionado){
        grafo[destino][origem] = pesoFinal;
    }

    if(arestaNova){
        numArestas++;
    }

    return true;
}

bool GrafoMatriz::removerAresta(int origem, int destino){
    if(!existeAresta(origem, destino)){
        return false;
    }

    grafo[origem][destino] = -1.0f;
    if(!direcionado){
        grafo[destino][origem] = -1.0f;
    }

    numArestas--;
    return true;
}

bool GrafoMatriz::existeAresta(int origem, int destino){
    if(origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices){
        return false;
    }

    return grafo[origem][destino] != -1.0f;
}

float GrafoMatriz::pesoAresta(int origem, int destino){
    if(!existeAresta(origem, destino)){
        return 0.0f;
    }

    return grafo[origem][destino];
}

void GrafoMatriz::imprimeGrafo(){
    int maxNumSize = to_string(grafo.size()).length();
    int colWidth = maxNumSize < 6 ? 6 : maxNumSize;
    int numVertices = grafo.size();

    for(int k = 0; k < colWidth; k++) cout << ' ';
    for(int j = 0; j < numVertices; j++){
        cout << setw(colWidth) << j;
    }
    cout << endl;

    for(int i = 0; i < numVertices; i++){
        cout << setw(colWidth - 2) << i << " |";
        for(int j = 0; j < numVertices; j++){
            if(grafo[i][j] == -1.0f){
                cout << setw(colWidth) << (ponderado ? "-" : "0");
            }else if(ponderado){
                cout << setw(colWidth) << fixed << setprecision(1) << grafo[i][j];
            }else{
                cout << setw(colWidth) << (int)grafo[i][j];
            }
        }
        cout << endl;
    }
}
