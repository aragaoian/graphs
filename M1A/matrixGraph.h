#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include <string>
#include <vector>
#include <map>
#include "graphCreator.h"

class GrafoMatriz : public Grafo {
private:
    std::vector<std::vector<float>> grafo;
    std::map<int, std::string> labels;
    virtual int indexMaximo();

public:
    bool criarGrafo(std::string path) override;

    bool inserirVertice(std::string label) override;
    bool removerVertice(int indice) override;
    std::string labelVertice(int indice) override;
    std::vector<int> retornarVertices() override;
    std::vector<int> retornarVizinhos(int vertice) override;

    bool inserirAresta(int origem, int destino, float peso) override;
    bool removerAresta(int origem, int destino) override;
    bool existeAresta(int origem, int destino) override;
    float pesoAresta(int origem, int destino) override;

    void imprimeGrafo() override;
};

#endif
