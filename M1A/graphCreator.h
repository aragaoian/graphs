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
    protected:
        int numVertices;
        int numArestas;
        bool direcionado;
        bool ponderado;

    public:
        Grafo() : numVertices(0), numArestas(0), direcionado(false), ponderado(false) {}
        virtual ~Grafo() {}

        virtual bool criarGrafo(string path = "") = 0;

        // Vértices
        virtual bool inserirVertice(string label = "") = 0;
        virtual bool removerVertice(int indice) = 0;
        virtual string labelVertice(int indice) = 0;
        virtual vector<int> retornarVizinhos(int vertice) = 0;

        // Arestas
        // virtual bool inserirAresta(int origem, int destino, float peso = 1) = 0;
        // virtual bool removerAresta(int origem, int destino) = 0;
        // virtual bool existeAresta(int origem, int destino) = 0;
        // virtual float pesoAresta(int origem, int destino) = 0;

        // Impressão
        virtual void imprimeGrafo() = 0;
        void imprimeInfos(); 
        
    };   

#endif