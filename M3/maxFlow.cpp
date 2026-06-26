#include "maxFlow.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>

using namespace std;

static const float EPS = 0.000001f;

static map<int, int> buildIndexMap(const vector<int> &vertices)
{
    map<int, int> idToIndex;
    for (int i = 0; i < static_cast<int>(vertices.size()); i++) {
        idToIndex[vertices[i]] = i;
    }
    return idToIndex;
}

static bool contemVertice(const vector<int> &vertices, int vertice)
{
    return find(vertices.begin(), vertices.end(), vertice) != vertices.end();
}

static bool buscaCaminhoAumentanteDFS(
    int atual,
    int destino,
    const vector<vector<float>> &residual,
    vector<bool> &visitados,
    vector<int> &anteriores)
{
    if (atual == destino) {
        return true;
    }

    visitados[atual] = true;

    for (int vizinho = 0; vizinho < static_cast<int>(residual[atual].size()); vizinho++) {
        if (visitados[vizinho] || residual[atual][vizinho] <= EPS) {
            continue;
        }

        anteriores[vizinho] = atual;
        if (buscaCaminhoAumentanteDFS(vizinho, destino, residual, visitados, anteriores)) {
            return true;
        }
    }

    return false;
}

vector<ArestaFluxo> extrairArestasFluxo(Grafo &grafo)
{
    vector<ArestaFluxo> arestas;
    vector<int> vertices = grafo.retornarVertices();

    for (int origem : vertices) {
        vector<int> vizinhos = grafo.retornarVizinhos(origem);
        for (int destino : vizinhos) {
            float capacidade = grafo.pesoAresta(origem, destino);
            if (capacidade <= EPS) {
                continue;
            }

            ArestaFluxo aresta;
            aresta.origem = origem;
            aresta.destino = destino;
            aresta.capacidade = capacidade;
            arestas.push_back(aresta);
        }
    }

    return arestas;
}

ResultadoFluxoMaximo fordFulkerson(
    const vector<int> &vertices,
    const vector<ArestaFluxo> &arestas,
    int origem,
    int destino)
{
    ResultadoFluxoMaximo resultado;
    resultado.fluxoMaximo = 0.0f;
    resultado.caminhosAumentantes = 0;

    if (vertices.empty() || origem == destino) {
        return resultado;
    }

    if (!contemVertice(vertices, origem) || !contemVertice(vertices, destino)) {
        return resultado;
    }

    map<int, int> idToIndex = buildIndexMap(vertices);
    int origemIdx = idToIndex[origem];
    int destinoIdx = idToIndex[destino];
    int n = static_cast<int>(vertices.size());

    vector<vector<float>> residual(n, vector<float>(n, 0.0f));
    for (const ArestaFluxo &aresta : arestas) {
        if (aresta.capacidade <= EPS) {
            continue;
        }

        if (idToIndex.find(aresta.origem) == idToIndex.end()
            || idToIndex.find(aresta.destino) == idToIndex.end()) {
            continue;
        }

        int u = idToIndex[aresta.origem];
        int v = idToIndex[aresta.destino];
        if (u == v) {
            continue;
        }

        residual[u][v] += aresta.capacidade;
    }

    while (true) {
        vector<bool> visitados(n, false);
        vector<int> anteriores(n, -1);

        if (!buscaCaminhoAumentanteDFS(origemIdx, destinoIdx, residual, visitados, anteriores)) {
            break;
        }

        float fluxoCaminho = numeric_limits<float>::infinity();
        for (int v = destinoIdx; v != origemIdx; v = anteriores[v]) {
            int u = anteriores[v];
            fluxoCaminho = min(fluxoCaminho, residual[u][v]);
        }

        for (int v = destinoIdx; v != origemIdx; v = anteriores[v]) {
            int u = anteriores[v];
            residual[u][v] -= fluxoCaminho;
            residual[v][u] += fluxoCaminho;
        }

        resultado.fluxoMaximo += fluxoCaminho;
        resultado.caminhosAumentantes++;
    }

    return resultado;
}

ResultadoFluxoMaximo fordFulkerson(Grafo &grafo, int origem, int destino) {
    vector<int> vertices = grafo.retornarVertices();
    vector<ArestaFluxo> arestas = extrairArestasFluxo(grafo);
    return fordFulkerson(vertices, arestas, origem, destino);
}

ResultadoBuscaLocalFluxo buscaLocalFluxoMaximo(Grafo &grafo, int origem, int destino)
{
    vector<int> vertices = grafo.retornarVertices();
    vector<ArestaFluxo> solucaoAtual = extrairArestasFluxo(grafo);
    ResultadoFluxoMaximo resultadoOriginal = fordFulkerson(vertices, solucaoAtual, origem, destino);

    ResultadoBuscaLocalFluxo resultado;
    resultado.fluxoOriginal = resultadoOriginal.fluxoMaximo;
    resultado.fluxoFinal = resultadoOriginal.fluxoMaximo;
    resultado.passos = 0;
    resultado.solucaoFinal = solucaoAtual;

    bool melhorou = true;
    while (melhorou) {
        melhorou = false;
        vector<ArestaFluxo> melhorVizinho = resultado.solucaoFinal;
        float melhorFluxoVizinho = resultado.fluxoFinal;

        for (int i = 0; i < static_cast<int>(resultado.solucaoFinal.size()); i++) {
            if (resultado.solucaoFinal[i].origem == resultado.solucaoFinal[i].destino) {
                continue;
            }

            vector<ArestaFluxo> vizinho = resultado.solucaoFinal;
            swap(vizinho[i].origem, vizinho[i].destino);

            ResultadoFluxoMaximo fluxoVizinho = fordFulkerson(vertices, vizinho, origem, destino);
            if (fluxoVizinho.fluxoMaximo > melhorFluxoVizinho + EPS) {
                melhorFluxoVizinho = fluxoVizinho.fluxoMaximo;
                melhorVizinho = vizinho;
                melhorou = true;
            }
        }

        if (melhorou) {
            resultado.solucaoFinal = melhorVizinho;
            resultado.fluxoFinal = melhorFluxoVizinho;
            resultado.passos++;
        }
    }

    return resultado;
}

void executeMaxFlow(Grafo &grafo)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> vertices = grafo.retornarVertices();
    if (vertices.empty()) {
        cout << "Grafo vazio." << endl;
        return;
    }

    int origem;
    int destino;

    cout << "\nFluxo Máximo" << endl;
    cout << "Vertice de origem: ";
    if (!(cin >> origem)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Vertice de destino: ";
    if (!(cin >> destino)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (!contemVertice(vertices, origem) || !contemVertice(vertices, destino)) {
        cout << "Vertice de origem ou destino invalido." << endl;
        return;
    }

    ResultadoFluxoMaximo fluxoOriginal = fordFulkerson(grafo, origem, destino);
    ResultadoBuscaLocalFluxo buscaLocal = buscaLocalFluxoMaximo(grafo, origem, destino);

    cout << "\n[Ford-Fulkerson]" << endl;
    cout << "Fluxo maximo da solucao original: " << fluxoOriginal.fluxoMaximo << endl;
    cout << "Caminhos aumentantes encontrados: " << fluxoOriginal.caminhosAumentantes << endl;

    cout << "\n[Busca Local]" << endl;
    cout << "Fluxo maximo da solucao final: " << buscaLocal.fluxoFinal << endl;
    cout << "Passos utilizados: " << buscaLocal.passos << endl;
}
