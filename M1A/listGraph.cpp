#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <algorithm>
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

        if(ponderado){
            float peso = stof(info[i][2]);
            aresta.peso = peso;
        }

        if(!direcionado){
            Aresta rev_aresta;
            rev_aresta.destino = vertice_origem;
            rev_aresta.peso = aresta.peso;
            grafo[vertice_destino].push_back(rev_aresta);
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
    /*
        * Remove o vertice pelo indice,
        * bem como remove todas as conexões
        * e também a referência no vetor de labels
        * (caso tenha).
    */
    try{
        for(auto& pair: grafo){
            int origem = pair.first;
            if(origem == indice) continue;

            vector<Aresta>& destinos = pair.second;
            vector<int> indexesToRemove;
            for(int i = 0; i < destinos.size(); i++){
                if(destinos[i].destino != indice) continue;
                indexesToRemove.push_back(i);
            }

            if(indexesToRemove.size() > 0){
                for(int indexToRemove: indexesToRemove){
                    grafo[origem].erase(destinos.begin() + indexToRemove);
                    numArestas--;
                }
            }
        }
        
        grafo.erase(indice);
        numVertices--;
        labels.erase(indice);

        return true;
    }catch(const runtime_error& e){
        return false;
    }
}

vector<int> GrafoList::retornarVizinhos(int indice){
    /*
        * Para digrafos a função retorna
        * apenas vértices N^+(v) ou seja v -> u.
        * Para grafos não direcionados a função
        * retorna ambos v <-> u.
    */
    vector<int> neighboors;
    if(grafo.find(indice) != grafo.end()){
        bool foundOrigem = false;
        for(const auto& pair: grafo){
            int origem = pair.first;
            if(origem != indice && direcionado){
                continue;   
            }else{
                foundOrigem = true;
            }

            vector<Aresta> arestas = pair.second;
            for(Aresta a: arestas){
                // Ainda falta testar essa parte do grafo n direcionado
                // Pedir pro amigo criar uns .txt grafos n dir (ponderado e não ponderado)
                if(indice != origem && !direcionado){
                    auto it = find_if(neighboors.begin(), neighboors.end(), [a](int i){return i == a.destino;});
                    if(it == neighboors.end()) continue;
                    neighboors.push_back(a.destino);
                }
                neighboors.push_back(a.destino);
            }

            if(foundOrigem) break;
        }
    }
    return neighboors;
}

string GrafoList::labelVertice(int indice){
    auto it = labels.find(indice);
    return it == labels.end() ? "Vértice não possui label." : it->second;
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