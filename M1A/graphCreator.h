#ifndef GRAPHCREATOR_H
#define GRAPHCREATOR_H

#include <vector>
#include <string>
#include <iostream>
#include <utility>

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
        Grafo(bool usr_opt_direcionado = false, bool usr_opt_ponderado = false)
            : numVertices(0),
              numArestas(0),
              direcionado(usr_opt_direcionado),
              ponderado(usr_opt_ponderado) {}
        virtual ~Grafo() {}

        virtual bool criarGrafo(std::string path = "") = 0;

        // Vértices
        virtual bool inserirVertice(std::string label = "") = 0;
        virtual bool removerVertice(int indice) = 0;
        virtual std::string labelVertice(int indice) = 0;
        virtual std::vector<int> retornarVizinhos(int vertice) = 0;
        virtual std::vector<int> retornarVertices() = 0;

        // Arestas
        virtual bool inserirAresta(int origem, int destino, float peso = 1) = 0;
        virtual bool removerAresta(int origem, int destino) = 0;
        virtual bool existeAresta(int origem, int destino) = 0;
        virtual float pesoAresta(int origem, int destino) = 0;

        // Impressão
        virtual void imprimeGrafo() = 0;
        // virtual void exportarGrafo() = 0;
        void imprimeInfos(); 
        std::vector<int> buscaLargura(int origem);
        std::vector<int> buscaProfundidade(int origem);
        std::vector<std::pair<int, float>> dijkstra(int origem);

    protected:
        void buscaProfundidadeAux(int vertice, std::vector<int>& visitados, std::vector<int>& ordem);
        
    };   

#endif
