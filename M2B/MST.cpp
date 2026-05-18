#include "MST.h"
#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <algorithm>
#include <numeric>

using namespace std;

//Usada em Kruskal para verificar se dois vértices estão na mesma árvore (ciclo)
struct UnionFind {
    //pai do vertice
    //altura aproximada da arvore
    vector<int> pai, rank_;
    //Inicializa n vertices, cada um em sua propria arvore
    UnionFind(int n) : pai(n), rank_(n, 0) {
        iota(pai.begin(), pai.end(), 0);
    }

    //Encontra o representante da arvore do vertice x (com path compression)
    int find(int x) {
        if (pai[x] != x) pai[x] = find(pai[x]);
        return pai[x];
    }
    //une conjuntos de x e y, retorna false se ja estavam unidos (ciclo), true se uniu com sucesso  
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank_[rx] < rank_[ry]) swap(rx, ry);
        pai[ry] = rx;
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
        return true;
    }
};

vector<ArestaMST> prim(
    Grafo &grafo,
    const vector<int> &vertices,
    const vector<int> &idToIndex,
    int raizIdx)
{
    int V = vertices.size();
    const float INF = numeric_limits<float>::infinity();

    // Q: vertices ainda nao incluidos na MST (true = ainda em Q)
    vector<bool> inQ(V, true);

    // S: conjunto solucao de arestas
    vector<ArestaMST> S;

    // Remove o vertice inicial A de Q]
    // O vértice inicial é a raiz da MST, então ele já está incluído na solução, e não deve ser considerado para adição de arestas.
    inQ[raizIdx] = false;

    // Enquanto Q nao estiver vazio
    // Executa até todos os vértices terem sido incluídos na MST.
    while (true)
    {
        // Verifica se ainda ha vertices em Q
        bool temEmQ = false;
        for (int i = 0; i < V; i++) {
            if (inQ[i]) { temEmQ = true; break; }
        }
        if (!temEmQ) break;

        // Encontra a menor aresta {u, v} onde u nao esta em Q e v esta em Q
        float menorPeso = INF;
        int melhorU = -1, melhorV = -1;

        for (int i = 0; i < V; i++) {
            if (inQ[i]) continue; // u deve estar fora de Q (ja na MST)
            int uId = vertices[i];

            for (int vId : grafo.retornarVizinhos(uId)) {
                int v = idToIndex[vId];
                if (!inQ[v]) continue; // v deve estar em Q

                float w = grafo.pesoAresta(uId, vId);
                if (w < menorPeso) { // encontrou uma aresta c/ menor peso
                    menorPeso = w;
                    melhorU   = i;
                    melhorV   = v;
                }
            }
        }

        if (melhorU == -1) break; // grafo desconexo

        // Adiciona aresta {u, v} ao conjunto solucao S
        ArestaMST a;
        a.origem  = vertices[melhorU];
        a.destino = vertices[melhorV];
        a.peso    = menorPeso;
        S.push_back(a);

        // Remove de Q o vertice que pertencia a ele (melhorV)
        inQ[melhorV] = false;
    }

    return S;
}

vector<ArestaMST> kruskal(
    Grafo &grafo,
    const vector<int> &vertices,
    const vector<int> &idToIndex)
{
    int V = vertices.size();

    // Inicia Q com todas as arestas do grafo (evita duplicatas em nao-direcionados)
    vector<ArestaMST> Q;
    for (int uId : vertices) {
        for (int vId : grafo.retornarVizinhos(uId)) {
            if (uId <= vId) { // Evita duplicatas em grafos nao-direcionados
                ArestaMST a;
                a.origem  = uId;
                a.destino = vId;
                a.peso    = grafo.pesoAresta(uId, vId);
                Q.push_back(a);
            }
        }
    }

    // Inicia floresta F: cada vertice e uma arvore isolada
    UnionFind F(V);

    // Conjunto solucao
    vector<ArestaMST> S;

    // Enquanto Q nao estiver vazio
    while (!Q.empty())
    {
        // Seleciona a menor aresta {u, v} de Q
        auto menorIt = min_element(Q.begin(), Q.end(), [](const ArestaMST &a, const ArestaMST &b) {
            return a.peso < b.peso;
        });
        ArestaMST aresta = *menorIt;

        // Remove a aresta {u, v} de Q
        Q.erase(menorIt);

        int u = idToIndex[aresta.origem];
        int v = idToIndex[aresta.destino];

        // Se u e v pertencem a arvores diferentes em F
        if (F.find(u) != F.find(v)) {
            // Adiciona {u, v} ao conjunto solucao S
            S.push_back(aresta);

            // Une as arvores de u e v em F
            F.unite(u, v);
        }
    }

    return S;
}

static void buildIndexMap(Grafo &grafo, vector<int> &vertices, vector<int> &idToIndex)
{
    vertices = grafo.retornarVertices();
    int maxId = *max_element(vertices.begin(), vertices.end());
    idToIndex.assign(maxId + 1, -1);
    for (int i = 0; i < (int)vertices.size(); i++)
        idToIndex[vertices[i]] = i;
}

static void runTimedMST(
    Grafo &grafo,
    const vector<int> &vertices,
    const vector<int> &idToIndex,
    int raizIdx,
    bool isPrim,
    const string &funcName)
{
    const int runs = 10000;
    vector<ArestaMST> mst;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < runs; i++) {
        if (isPrim)
            mst = prim(grafo, vertices, idToIndex, raizIdx);
        else
            mst = kruskal(grafo, vertices, idToIndex);
    }

    auto end = chrono::high_resolution_clock::now();
    auto total = chrono::duration_cast<chrono::milliseconds>(end - start);
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

// ---------------------------------------------------------------------------
// Entrada de menu
// ---------------------------------------------------------------------------
void executeMST(Grafo &grafo)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nAlgoritmos de Arvore Geradora Minima" << endl;
    cout << "1 - Prim" << endl;
    cout << "2 - Kruskal" << endl;
    cout << "0 - Voltar" << endl;
    cout << "Opcao: ";

    int opt;
    if (!(cin >> opt)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (opt == 0) return;

    vector<int> vertices;
    vector<int> idToIndex;
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