#include <iostream>
#include <string>
#include <format>
#include <algorithm>
#include <limits>
#include <map>
#include "graphCreator.h"

using namespace std;

void Grafo::imprimeInfos(){
    cout << format("Total de vertices: {}", numVertices) << endl;
    cout << format("Total de arestas: {}", numArestas) << endl;
    cout << format("Direcionado: {}", direcionado ? "sim" : "nao") << endl;
    cout << format("Ponderado: {}", ponderado ? "sim" : "nao") << endl;
}

vector<int> Grafo::buscaLargura(int origem){
    vector<int> vertices = retornarVertices();
    if(find(vertices.begin(), vertices.end(), origem) == vertices.end()){
        return {};
    }

    vector<int> visitados;
    vector<int> fila = {origem};
    vector<int> ordem;

    while(!fila.empty()){
        int atual = fila.front();
        fila.erase(fila.begin());

        if(find(visitados.begin(), visitados.end(), atual) != visitados.end()){
            continue;
        }

        visitados.push_back(atual);
        ordem.push_back(atual);

        for(int vizinho: retornarVizinhos(atual)){
            if(find(visitados.begin(), visitados.end(), vizinho) == visitados.end()){
                fila.push_back(vizinho);
            }
        }
    }

    return ordem;
}

void Grafo::buscaProfundidadeAux(int vertice, vector<int>& visitados, vector<int>& ordem){
    if(find(visitados.begin(), visitados.end(), vertice) != visitados.end()){
        return;
    }

    visitados.push_back(vertice);
    ordem.push_back(vertice);

    for(int vizinho: retornarVizinhos(vertice)){
        buscaProfundidadeAux(vizinho, visitados, ordem);
    }
}

vector<int> Grafo::buscaProfundidade(int origem){
    vector<int> vertices = retornarVertices();
    if(find(vertices.begin(), vertices.end(), origem) == vertices.end()){
        return {};
    }

    vector<int> visitados;
    vector<int> ordem;
    buscaProfundidadeAux(origem, visitados, ordem);
    return ordem;
}

vector<pair<int, float>> Grafo::dijkstra(int origem){
    vector<int> vertices = retornarVertices();
    if(find(vertices.begin(), vertices.end(), origem) == vertices.end()){
        return {};
    }

    map<int, float> distancias;
    map<int, int> anteriores;
    vector<int> naoVisitados = vertices;

    for(int vertice: vertices){
        distancias[vertice] = numeric_limits<float>::infinity();
        anteriores[vertice] = -1;
    }

    distancias[origem] = 0.0f;

    while(!naoVisitados.empty()){
        auto atualIt = min_element(
            naoVisitados.begin(),
            naoVisitados.end(),
            [&distancias](int a, int b){
                return distancias[a] < distancias[b];
            }
        );

        int atual = *atualIt;
        naoVisitados.erase(atualIt);

        if(distancias[atual] == numeric_limits<float>::infinity()){
            continue;
        }

        for(int vizinho: retornarVizinhos(atual)){
            float peso = ponderado ? pesoAresta(atual, vizinho) : 1.0f;
            float novaDistancia = distancias[atual] + peso;

            if(novaDistancia < distancias[vizinho]){
                distancias[vizinho] = novaDistancia;
                anteriores[vizinho] = atual;
            }
        }
    }

    vector<pair<int, float>> resultado;
    for(int vertice: vertices){
        resultado.push_back({vertice, distancias[vertice]});

        cout << "Vertice " << vertice << " | Distancia: ";
        if(distancias[vertice] == numeric_limits<float>::infinity()){
            cout << "infinito | Caminho: inexistente" << endl;
            continue;
        }

        cout << distancias[vertice] << " | Caminho: ";

        vector<int> caminho;
        for(int atual = vertice; atual != -1; atual = anteriores[atual]){
            caminho.push_back(atual);
        }

        reverse(caminho.begin(), caminho.end());

        for(int i = 0; i < caminho.size(); i++){
            cout << caminho[i];
            if(i + 1 < caminho.size()){
                cout << " -> ";
            }
        }
        cout << endl;
    }

    return resultado;
}
