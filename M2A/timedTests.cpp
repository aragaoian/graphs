#include "timedTests.h"
#include "coloring.h"
#include "utils.h"
#include <string>
#include <vector>
#include <chrono>
#include <iostream>

void timedTests(std::vector<std::vector<int>> &adj, int V, std::vector<int> &color, int (func)(std::vector<std::vector<int>> &, int, std::vector<int> &), Grafo &grafo, std::string funcName){
    int runs = 1;
    int colors;

    auto start = std::chrono::high_resolution_clock::now();

    // NOTE
    // usar a média de runs pois para grafos muito pequenos
    // o tempo de execucão em ns/ms fica como 0
    for(int i = 0; i < runs; i++){
        colors = func(adj, V, color);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    double avgTime = static_cast<double>(time.count()) / runs;

    std::cout << "\n[" << funcName << "]" << std::endl;
    std::cout << "Cores: " << colors << std::endl;
    std::cout << "Tempo médio (para n = " << runs << "):" << avgTime << " ms" << std::endl;
    printColoring(color, V);
}

void executeTimedTests(Grafo &grafo){
    std::vector<std::vector<int>> adj = buildAdjList(grafo);
    int V = adj.size();
    std::vector<int> color;

    if(V > 31){
        std::cout << "Pulando Força Bruta pois V > 31." << std::endl;
    }else{
        timedTests(adj, V, color, bruteForceColoring, grafo, "Força Bruta");
    }

    timedTests(adj, V, color, greedyColoring, grafo, "Guloso");
    timedTests(adj, V, color, welshPowell, grafo, "Welsh Powell");
    timedTests(adj, V, color, dsatur, grafo, "DSatur");
}