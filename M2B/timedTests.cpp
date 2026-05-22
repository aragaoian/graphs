#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "../M1A/graphCreator.h"
#include "MST.h"

void buildIndexMap(Grafo &grafo, std::vector<int> &vertices, std::vector<int> &idToIndex)
{
    vertices = grafo.retornarVertices();
    int maxId = *max_element(vertices.begin(), vertices.end());
    idToIndex.assign(maxId + 1, -1);
    for (int i = 0; i < (int)vertices.size(); i++)
        idToIndex[vertices[i]] = i;
}

static void runTimedMST(
    Grafo &grafo,
    const std::vector<int> &vertices,
    const std::vector<int> &idToIndex,
    int raizIdx,
    bool isPrim,
    const std::string &funcName
){
    const int runs = 1;
    std::vector<ArestaMST> mst;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < runs; i++) {
        if (isPrim)
            mst = prim(grafo, vertices, idToIndex, raizIdx);
        else
            mst = kruskal(grafo, vertices, idToIndex);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    double avgTime = static_cast<double>(total.count()) / runs;

    float soma = 0.0f;
    for (auto &a : mst) soma += a.peso;

    cout << "\n[" << funcName << "] Arvore Geradora Minima:" << endl;
    for (auto &a : mst) {
        cout << "  " << a.origem << " -- " << a.destino
             << "  (peso: " << a.peso << ")" << endl;
    }
    cout << "Soma total das arestas: " << soma << endl;
    cout << "Tempo medio (para n = " << runs << "): " << avgTime << " ms" << endl;
}


void executeMST(Grafo &grafo)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nAlgoritmos de Arvore Geradora Minima" << endl;
    cout << "1 - Prim" << endl;
    cout << "2 - Kruskal" << endl;
    cout << "0 - Voltar" << endl;

    int opt;
    if (!(cin >> opt)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (opt == 0) return;

    std::vector<int> vertices;
    std::vector<int> idToIndex;
    buildIndexMap(grafo, vertices, idToIndex);

    if (vertices.empty()) {
        cout << "Grafo vazio." << endl;
        return;
    }

    if (opt == 1) {
        int raizId;
        cout << "Vertice raiz para Prim: ";
        if (!(cin >> raizId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (idToIndex[raizId] == -1) {
            cout << "Vertice invalido." << endl;
            return;
        }

        runTimedMST(grafo, vertices, idToIndex, idToIndex[raizId], true, "Prim");
    } else if (opt == 2) {
        runTimedMST(grafo, vertices, idToIndex, 0, false, "Kruskal");
    }
}