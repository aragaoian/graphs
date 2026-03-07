#ifndef GRAPHCREATOR_H
#define GRAPHCREATOR_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Aresta {
    int destino;
    float peso;
};

class Grafo {
    private:
        int numVertices;
        int numArestas;
        bool direcionado;
        bool ponderado;

    public:
        Grafo(int vertices, int arestas, bool dir, bool pond);
        ~Grafo();

        // Vértices
        bool inserirVertice(string label);
        bool removerVertice(int indice);
        string labelVertice(int indice);
        vector<int> retornarVizinhos(int vertice);

        // Arestas
        bool inserirAresta(int origem, int destino, float peso = 1);
        bool removerAresta(int origem, int destino);
        bool existeAresta(int origem, int destino);
        float pesoAresta(int origem, int destino);

        // Impressão
        void imprimeGrafo();
};

#endif