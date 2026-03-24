#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <algorithm>
#include "listGraph.h"
#include "graphReader.h"

using namespace std;

bool GrafoList::criarGrafo(string path) {
    if(path.empty()) return false;

    grafo.clear();
    labels.clear();

    vector<string> info = lerGrafo(path);

    if(info.size() < 4) return false;
    if((info.size() - 4) % 3 != 0) return false;

    int casted_vertices = stoi(info[0]);
    int casted_arestas = stoi(info[1]);
    int casted_direcionado = stoi(info[2]);
    int casted_ponderado = stoi(info[3]);

    numVertices = casted_vertices;
    numArestas = casted_arestas;
    direcionado = (casted_direcionado == 1);
    ponderado = (casted_ponderado == 1);

    for(int i = 4; i < info.size() - 2; i += 3){
        int vertice_origem = stoi(info[i]);
        int vertice_destino = stoi(info[i + 1]);
        
        Aresta aresta;
        aresta.destino = vertice_destino;
        aresta.peso = 0.0f;

        if(ponderado){
            float peso = stof(info[i + 2]);
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
    int newIndex = indexMaximo() + 1;
    grafo[newIndex];
    if(label != "") labels[newIndex] = label;
    numVertices++;
    cout << "Vértice com índice" << newIndex << " e label " <<  label << " ADICIONADO" << endl;
    return true;
}

bool GrafoList::removerVertice(int indice){
    /*
        * Remove o vertice pelo indice,
        * bem como remove todas as conexões
        * e também a referência no vetor de labels
        * (caso tenha).
    */

    if(grafo.find(indice) == grafo.end()) return false;

    int origemDestino = 0;
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
            // Remover em ordem DESC para não
            // alterar a ordem dos índices
            // Essa parte só serve pra remover as referências
            // (Ou seja, não há mais arestas se não houver mais o vértice)
            sort(indexesToRemove.begin(), indexesToRemove.end(), greater<int>());
            for(int indexToRemove: indexesToRemove){
                grafo.at(origem).erase(destinos.begin() + indexToRemove);
                origemDestino++;
            }
        }
    }

    int destinoOrigem = static_cast<int>(grafo.at(indice).size());
    if(direcionado){
        numArestas -= (origemDestino + destinoOrigem);
    } else {
        numArestas -= origemDestino;
    }

    if(numArestas < 0) numArestas = 0;
    grafo.erase(indice);
    numVertices--;
    labels.erase(indice);
    cout << "Vértice com índice " << indice << " REMOVIDO" << endl;
    return true;
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
    if(grafo.find(origem) == grafo.end()) return false;
    if(grafo.find(destino) == grafo.end()) return false;

    // Aresta com destino para destino já existe
    vector<Aresta>& origemArestas = grafo.at(origem);
    auto origemIt = find_if(origemArestas.begin(), origemArestas.end(), [destino](Aresta a){return a.destino == destino;});
    if(origemIt != origemArestas.end()) return false;

    if(!direcionado){
        // Aresta com destino para origem já existe
        vector<Aresta>& destinoArestas = grafo.at(destino);
        auto origemIt = find_if(destinoArestas.begin(), destinoArestas.end(), [origem](Aresta a){return a.destino == origem;});
        if(origemIt != destinoArestas.end()) return false;

        if(origem != destino){
            Aresta nonDirectAresta;
            nonDirectAresta.destino = origem;
            nonDirectAresta.peso = ponderado ? peso : 0.0f;
            grafo.at(destino).push_back(nonDirectAresta);
        }
    }

    Aresta directAresta = {destino, ponderado ? peso : 0.0f};
    grafo.at(origem).push_back(directAresta);
    numArestas++;
    cout << "Aresta ADICIONADO com origem " << origem << ", destino " << destino << " e peso " << peso << endl;
    return true;
}

bool GrafoList::removerAresta(int origem, int destino){
    if(grafo.find(origem) == grafo.end()) return false;
    if(grafo.find(destino) == grafo.end()) return false;

    if(!direcionado){
        vector<Aresta>& destinoArestas = grafo.at(destino);
        auto origemIt = find_if(destinoArestas.begin(), destinoArestas.end(), [origem](Aresta a){return a.destino == origem;});
        if(origemIt == destinoArestas.end()) return false;
        int indexOrigemAresta = distance(destinoArestas.begin(), origemIt);
        destinoArestas.erase(destinoArestas.begin() + indexOrigemAresta);
    }

    vector<Aresta>& origemArestas = grafo.at(origem);
    auto destinoIt = find_if(origemArestas.begin(), origemArestas.end(), [destino](Aresta a){return a.destino == destino;});
    if(destinoIt == origemArestas.end()) return false;
    int indexDestinoAresta = distance(origemArestas.begin(), destinoIt);
    origemArestas.erase(origemArestas.begin() + indexDestinoAresta);

    numArestas--;
    cout << "Aresta REMOVIDA com origem " << origem << " e destino " << destino << endl;
    return true;
}

bool GrafoList::existeAresta(int origem, int destino){
    if(grafo.find(origem) == grafo.end()) return false;

    vector<Aresta>& origemArestas = grafo.at(origem);
    auto it = find_if(origemArestas.begin(), origemArestas.end(), [destino](Aresta a){return a.destino == destino;});
    return it != origemArestas.end() ? true : false;
}

float GrafoList::pesoAresta(int origem, int destino){
    if(grafo.find(origem) == grafo.end()) return 0.0f;

    vector<Aresta>& origemArestas = grafo.at(origem);
    auto it = find_if(origemArestas.begin(), origemArestas.end(), [destino](Aresta a){return a.destino == destino;});
    if(it == origemArestas.end()) return 0.0f;

    return it->peso;
}

void GrafoList::imprimeGrafo() {
    for(const auto& pair: grafo){
        int origem = pair.first;
        vector<Aresta> destinos = pair.second;
        
        string label = "";
        if(labels.find(origem) != labels.end()) label = labels.at(origem);

        cout << format("Origem: {} | Label: {}", origem, label);
        for(Aresta a: destinos){
            string formatted_aresta = format("(Destino: {} | Peso: {})", a.destino, a.peso);
            cout << " -> " << formatted_aresta;
        }
        cout << endl;
    }
}