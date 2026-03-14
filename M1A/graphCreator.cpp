#include <iostream>
#include <string>
#include <format>
#include "graphCreator.h"

using namespace std;

void Grafo::imprimeInfos(){
    cout << format("Total de vértices: {}", numVertices) << endl;
    cout << format("Total de arestas: {}", numArestas) << endl;
    cout << format("Direcionado: {}", direcionado ? "sim" : "não") << endl;
    cout << format("Ponderado: {}", ponderado ? "sim" : "não") << endl;
}