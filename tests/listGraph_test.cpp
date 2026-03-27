#include <cassert>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <tuple>

#include "../M1A/listGraph.h"

namespace {

constexpr int kNumVertices = 20;
constexpr float kEpsilon = 1e-5f;

struct FixturePaths {
    std::string directedWeighted;
    std::string directedUnweighted;
    std::string undirectedWeighted;
    std::string undirectedUnweighted;
    std::string isolated_directed_graph;
};

const FixturePaths paths{
    "tests/generated/directed_weighted_80.txt",
    "tests/generated/directed_unweighted_80.txt",
    "tests/generated/undirected_weighted_80.txt",
    "tests/generated/undirected_unweighted_80.txt",
    "tests/generated/isolated_directed_graph.txt"
};

bool nearlyEqual(float a, float b, float eps = kEpsilon) {
    return std::fabs(a - b) <= eps;
}

float deterministicWeight(int origem, int destino) {
    const int raw = (origem * 37 + destino * 11 + 13) % 97;
    return 1.0f + static_cast<float>(raw) / 10.0f;
}

void testCreateGraphForAllModes(const FixturePaths& paths) {
    {
        GrafoList g;
        assert(g.criarGrafo(paths.directedWeighted));
        assert(g.existeAresta(0, 1));
        assert(!g.existeAresta(1, 0));
        assert(nearlyEqual(g.pesoAresta(0, 1), deterministicWeight(0, 1)));
    }

    {
        GrafoList g;
        assert(g.criarGrafo(paths.directedUnweighted));
        assert(g.existeAresta(0, 1));
        assert(!g.existeAresta(1, 0));
        assert(nearlyEqual(g.pesoAresta(0, 1), 0.0f));
    }

    {
        GrafoList g;
        assert(g.criarGrafo(paths.undirectedWeighted));
        assert(g.existeAresta(0, 1));
        assert(g.existeAresta(1, 0));
        assert(nearlyEqual(g.pesoAresta(0, 1), deterministicWeight(0, 1)));
        assert(nearlyEqual(g.pesoAresta(1, 0), deterministicWeight(0, 1)));
    }

    {
        GrafoList g;
        assert(g.criarGrafo(paths.undirectedUnweighted));
        assert(g.existeAresta(0, 1));
        assert(g.existeAresta(1, 0));
        assert(nearlyEqual(g.pesoAresta(0, 1), 0.0f));
        assert(nearlyEqual(g.pesoAresta(1, 0), 0.0f));
    }

    {
        GrafoList g;
        assert(!g.criarGrafo(""));
        assert(!g.criarGrafo("tests/generated/does_not_exist.txt"));
    }
}

void testIsolatedVerticesAndZeroEdgeGraph(const FixturePaths& paths) {
    GrafoList g;
    assert(g.criarGrafo(paths.isolated_directed_graph));

    // Vertices existem mesmo sem arestas
    assert(g.inserirAresta(0, 1, 1.0f));
    assert(g.existeAresta(0, 1));

    // Não pode deixar inserir
    // em vértices não existentes
    assert(!g.inserirAresta(0, 99, 1.0f));

    std::filesystem::remove(paths.isolated_directed_graph);
}

void testVertexFunctions() {
    GrafoList g;

    assert(g.inserirVertice("A"));
    assert(g.inserirVertice("B"));
    assert(g.inserirVertice(""));

    assert(g.labelVertice(0) == "A");
    assert(g.labelVertice(1) == "B");
    assert(g.labelVertice(2) == "Vértice não possui label.");
    assert(g.labelVertice(99) == "Vértice não possui label.");

    assert(g.inserirAresta(0, 1, 5.0f));
    assert(g.inserirAresta(1, 2, 2.5f));

    const auto vizinhos0 = g.retornarVizinhos(0);
    assert(!vizinhos0.empty());

    const auto vizinhos1 = g.retornarVizinhos(1);
    assert(!vizinhos1.empty());

    assert(g.removerVertice(1));
    assert(!g.existeAresta(0, 1));
    assert(g.labelVertice(1) == "Vértice não possui label.");

    assert(!g.removerVertice(999));
}

void testEdgeFunctions() {
    GrafoList g;

    assert(g.inserirVertice("v0"));
    assert(g.inserirVertice("v1"));
    assert(g.inserirVertice("v2"));

    assert(g.inserirAresta(0, 1, 7.0f));
    assert(g.existeAresta(0, 1));
    assert(g.existeAresta(1, 0));

    // Tentar inserir arestas iguais
    assert(!g.inserirAresta(0, 1, 7.0f));

    assert(nearlyEqual(g.pesoAresta(0, 1), 0.0f));
    assert(nearlyEqual(g.pesoAresta(9, 10), 0.0f));

    assert(g.removerAresta(0, 1));
    assert(!g.existeAresta(0, 1));
    assert(!g.existeAresta(1, 0));

    assert(!g.removerAresta(0, 1));
    assert(!g.inserirAresta(0, 99, 1.0f));
    assert(!g.inserirAresta(99, 0, 1.0f));
}

void testPrintFunctionsSmoke() {
    GrafoList g;

    assert(g.inserirVertice("A"));
    assert(g.inserirVertice("B"));
    assert(g.inserirVertice("C"));
    assert(g.inserirAresta(0, 1, 1.0f));
    assert(g.inserirAresta(1, 2, 1.0f));

    g.imprimeInfos();
    g.imprimeGrafo();
}

}

int main() {
    testCreateGraphForAllModes(paths);
    testIsolatedVerticesAndZeroEdgeGraph(paths);
    testVertexFunctions();
    testEdgeFunctions();
    testPrintFunctionsSmoke();

    std::cout << "All deterministic GrafoList tests passed.\n";
    return 0;
}
