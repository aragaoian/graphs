#include "../M1A/graphCreator.h"
#include "utils.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

// TODO
// verificar se os IDs são contíguos
// caso contrário precisa mapaear (da uma olhada nisso)
std::vector<std::vector<int>> buildAdjList(Grafo &grafo)
{
    std::vector<int> vertices = grafo.retornarVertices();
    int V = vertices.size();

    std::vector<int> sorted = vertices;
    std::sort(sorted.begin(), sorted.end());

    bool contiguous = (sorted.size() == static_cast<size_t>(V));
    for (int i = 0; i < V && contiguous; i++)
    {
        if (sorted[i] != i)
        {
            contiguous = false;
        }
    }

    std::vector<std::vector<int>> adj(V);

    if (contiguous)
    {
        for (int v : vertices)
        {
            std::vector<int> vizinhos = grafo.retornarVizinhos(v);
            adj[v] = vizinhos;
        }
        return adj;
    }

    std::unordered_map<int, int> idToIndex;
    idToIndex.reserve(vertices.size());
    for (int i = 0; i < V; i++)
    {
        idToIndex[vertices[i]] = i;
    }

    for (int v : vertices)
    {
        int idx = idToIndex[v];
        std::vector<int> vizinhos = grafo.retornarVizinhos(v);
        std::vector<int> mapped;
        mapped.reserve(vizinhos.size());
        for (int u : vizinhos)
        {
            mapped.push_back(idToIndex[u]);
        }
        adj[idx] = std::move(mapped);
    }

    return adj;
}