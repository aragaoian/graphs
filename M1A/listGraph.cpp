#include <iostream>
#include <vector>
#include <string>
#include <format>
#include "listGraph.h"
#include "graphReader.h"

using namespace std;

bool GrafoList::criarGrafo(string path) {
    if(path == "") return false;
    vector<vector<string>> info = lerGrafo(path);

    int casted_vertices = stoi(info[0][0]);
    int casted_arestas = stoi(info[0][1]);
    int casted_direcionado = stoi(info[0][2]);
    int casted_ponderado = stoi(info[0][3]);

    numVertices = casted_vertices;
    numArestas = casted_arestas;
    direcionado = true ? casted_direcionado == 1 : false;
    ponderado = true ? casted_ponderado == 1 : false;

    for(int i = 1; i < info.size(); i++){
        int vertice_origem = stoi(info[i][0]);
        int vertice_destino = stoi(info[i][1]);
        
        Aresta aresta;
        aresta.destino = vertice_destino;
        aresta.peso = 0.0f;

        if(!direcionado){
            Aresta rev_aresta;
            rev_aresta.destino = vertice_origem;
            rev_aresta.peso = 0.0f;
            grafo[vertice_destino].push_back(rev_aresta);
        }

        if(ponderado){
            float peso = stof(info[i][2]);
            aresta.peso = peso;
        }

        grafo[vertice_origem].push_back(aresta);
    }

    return true;
}

int GrafoList::indexMaximo(){
    int maxVerticeIndex = -1;
    for(const auto& pair: grafo){
        int verticeIndex = pair.first;
        if (verticeIndex > maxVerticeIndex){
            maxVerticeIndex = verticeIndex;
        }
    }
    return maxVerticeIndex;
}

bool GrafoList::inserirVertice(string label){
    try{
        int newIndex = indexMaximo() + 1;
        grafo[newIndex];
        if(label != "") labels[newIndex] = label;
        numVertices++;
        return true;
    }catch (const runtime_error& e){
        return false;
    }
}

bool GrafoList::removerVertice(int indice){
    try{
        // implement
        return true;
    }catch(const runtime_error& e){
        return false;
    }
}

void GrafoList::imprimeGrafo() {
    for(const auto& pair: grafo){
        int origem = pair.first;
        vector<Aresta> destinos = pair.second;
        
        cout << format("Origem: {} | Label: {}", origem, labels[origem]);
        for(Aresta a: destinos){
            string formatted_aresta = format("(Destino: {} | Peso: {})", a.destino, a.peso);
            cout << " -> " << formatted_aresta;
        }
        cout << endl;
    }
}