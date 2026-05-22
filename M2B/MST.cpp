#include "MST.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <algorithm>
#include <numeric>

std::vector<ArestaMST> prim(
    Grafo &grafo,
    const std::vector<int> &vertices,
    const std::vector<int> &idToIndex,
    int raizIdx)
{
    /*
        - Q: vertices ainda nao incluidos na MST (true = ainda em Q)
        - S: conjunto solucao de arestas
    */
    int V = vertices.size();
    const float INF = numeric_limits<float>::infinity();
    std::vector<bool> inQ(V, true);
    std::vector<ArestaMST> S;

    // Remove o vertice inicial A de Q]
    // O vértice inicial é a raiz da MST, então ele já está 
    // incluído na solução, e não deve ser considerado para adição de arestas.
    inQ[raizIdx] = false;

    // 
    while (true)
    {
        bool isQEmpty = false;
        for (int i = 0; i < V; i++) {
            if (inQ[i]) { 
                isQEmpty = true; 
                break; 
            }
        }
        if (!isQEmpty) break;

        // Encontra a menor aresta {u, v} 
        // onde u não está em Q e v está em Q
        float bestWeight = INF;
        int bestU = -1;
        int bestV = -1;

        for (int i = 0; i < V; i++) {
            if (inQ[i]) continue;
            int uId = vertices[i];

            for (int vId : grafo.retornarVizinhos(uId)) {
                int v = idToIndex[vId];
                if (!inQ[v]) continue;

                float w = grafo.pesoAresta(uId, vId);
                if (w < bestWeight) {
                    bestWeight = w;
                    bestU   = i;
                    bestV   = v;
                }
            }
        }

        if (bestU == -1) break; // ignorar grafo desconexo

        ArestaMST a;
        a.origem = vertices[bestU];
        a.destino = vertices[bestV];
        a.peso = bestWeight;
        S.push_back(a);

        // Remove de Q o vertice que pertencia a ele
        inQ[bestV] = false;
    }

    return S;
}

std::vector<ArestaMST> kruskal(
    Grafo &grafo,
    const std::vector<int> &vertices,
    const std::vector<int> &idToIndex
){
    /*
        - Q: vertices ainda nao incluidos na MST (true = ainda em Q)
        - F: inicia floresta, onde cada vertice é uma arvore isolada
        - S: conjunto solucao de arestas
    */
    int V = vertices.size();
    
    // Inicia Q com todas as arestas do grafo 
    // (evita duplicatas em nao-direcionados)
    std::vector<ArestaMST> Q;
    for (int uId : vertices) {
        for (int vId : grafo.retornarVizinhos(uId)) {
            if (uId <= vId) {
                ArestaMST a;
                a.origem  = uId;
                a.destino = vId;
                a.peso    = grafo.pesoAresta(uId, vId);
                Q.push_back(a);
            }
        }
    }

    UnionFind F(V);
    std::vector<ArestaMST> S;
    

    while (!Q.empty())
    {
        // Seleciona a menor aresta {u, v} de Q
        auto smallestAresta = min_element(Q.begin(), Q.end(), [](const ArestaMST &a, const ArestaMST &b) {
            return a.peso < b.peso;
        });
        ArestaMST aresta = *smallestAresta;

        Q.erase(smallestAresta);

        int u = idToIndex[aresta.origem];
        int v = idToIndex[aresta.destino];

        // Se u e v pertencem a arvores diferentes em F
        if (F.find(u) != F.find(v)) {
            S.push_back(aresta); // Adiciona {u, v} ao conjunto solucao S
            F.unite(u, v); // Une as arvores de u e v em F
        }
    }

    return S;
}