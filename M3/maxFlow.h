#ifndef MAXFLOW_H
#define MAXFLOW_H

#include "../M1A/graphCreator.h"
#include <vector>

struct ArestaFluxo {
    int origem;
    int destino;
    float capacidade;
};

struct ResultadoFluxoMaximo {
    float fluxoMaximo;
    int caminhosAumentantes;
};

struct ResultadoBuscaLocalFluxo {
    float fluxoOriginal;
    float fluxoFinal;
    int passos;
    std::vector<ArestaFluxo> solucaoFinal;
};

std::vector<ArestaFluxo> extrairArestasFluxo(Grafo &grafo);

ResultadoFluxoMaximo fordFulkerson(
    const std::vector<int> &vertices,
    const std::vector<ArestaFluxo> &arestas,
    int origem,
    int destino
);

ResultadoFluxoMaximo fordFulkerson(Grafo &grafo, int origem, int destino);

ResultadoBuscaLocalFluxo buscaLocalFluxoMaximo(Grafo &grafo, int origem, int destino);

void executeMaxFlow(Grafo &grafo);

#endif
