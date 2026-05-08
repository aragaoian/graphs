#include "utils.h"
#include "../M1A/graphCreator.h"
#include <vector>

// TODO
// verificar se os IDs são contíguos
// caso contrário precisa mapaear (da uma olhada nisso)
std::vector<std::vector<int>> buildAdjList(Grafo &grafo)
{
    std::vector<int> vertices = grafo.retornarVertices();
    int V = vertices.size();

    std::vector<std::vector<int>> adj(V);

    for (int v : vertices)
    {
        std::vector<int> vizinhos = grafo.retornarVizinhos(v);
        adj[v] = vizinhos;
    }

    return adj;
}