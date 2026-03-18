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
            Aresta revAresta;
            revAresta.destino = vertice_origem;
            revAresta.peso = aresta.peso;
            grafo[vertice_destino].push_back(revAresta);
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
        // Procurar utilizar por ref nas próximas 
        // pra evitir ficar copiando o vector
        vector<Aresta>& arestas = grafo.at(indice);
        for(Aresta a: arestas){
            neighboors.push_back(a.destino);
        }
    }
    return neighboors;
}

string GrafoList::labelVertice(int indice){
    auto it = labels.find(indice);
    return it == labels.end() ? "Vértice não possui label." : it->second;
}

bool GrafoList::inserirAresta(int origem, int destino, float peso){
    try{
        if(grafo.find(origem) == grafo.end()) return false;

        if(!direcionado){
            if(grafo.find(destino) == grafo.end()) return false;
            Aresta nonDirectAresta;
            nonDirectAresta.destino = origem;
            nonDirectAresta.peso = ponderado ? peso : 0.0f;
            grafo.at(destino).push_back(nonDirectAresta);
        }

        Aresta directAresta = {destino, ponderado ? peso : 0.0f};
        grafo.at(origem).push_back(directAresta);
        numArestas++;
        return true;
    }catch(const runtime_error& e){
        return false;
    }
}

bool GrafoList::removerAresta(int origem, int destino){
    try{
        if(grafo.find(origem) == grafo.end()) return false;

        if(!direcionado){
            if(grafo.find(destino) == grafo.end()) return false;
            vector<Aresta>& destinoArestas = grafo.at(destino);
            auto origemIt = find_if(destinoArestas.begin(), destinoArestas.end(), [origem](Aresta a){return a.destino == origem;});
            int indexOrigemAresta = distance(destinoArestas.begin(), origemIt);
            destinoArestas.erase(destinoArestas.begin() + indexOrigemAresta);
        }

        vector<Aresta>& origemArestas = grafo.at(origem);
        auto origemIt = find_if(origemArestas.begin(), origemArestas.end(), [destino](Aresta a){return a.destino == destino;});
        int indexOrigemAresta = distance(origemArestas.begin(), origemIt);
        origemArestas.erase(origemArestas.begin() + indexOrigemAresta);

        numArestas--;
        return true;
    }catch(const runtime_error& e){
        return false;
    }
}

bool GrafoList::existeAresta(int origem, int destino){
    if(grafo.find(origem) == grafo.end()) return false;

    vector<Aresta>& origemArestas = grafo.at(origem);
    auto it = find_if(origemArestas.begin(), origemArestas.end(), [destino](Aresta a){return a.destino == destino;});
    return it != origemArestas.end() ? true : false;
}

float GrafoList::pesoAresta(int origem, int destino){
    if(grafo.find(origem) == grafo.end()) return false;

    vector<Aresta>& origemArestas = grafo.at(origem);
    auto it = find_if(origemArestas.begin(), origemArestas.end(), [destino](Aresta a){return a.destino == destino;});
    if(it == origemArestas.end()) return 0.0f;
    
    int index = distance(origemArestas.begin(), it);
    return origemArestas.at(index).peso;
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