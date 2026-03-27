#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <string>
#include <map>
#include <vector>
#include "graphCreator.h"

class GrafoList : public Grafo {
private:
	std::map<int, std::vector<Aresta>> grafo;
	std::map<int, std::string> labels;
	virtual int indexMaximo();
	
public:
	bool criarGrafo(std::string path) override;

    bool inserirVertice(std::string label) override;
    bool removerVertice(int indice) override;
	std::string labelVertice(int indice) override;
	std::vector<int> retornarVizinhos(int vertice) override;
	std::vector<int> retornarVertices() override;

	bool inserirAresta(int origem, int destino, float peso) override;
	bool removerAresta(int origem, int destino) override;
	bool existeAresta(int origem, int destino) override;
	float pesoAresta(int origem, int destino) override;

	void imprimeGrafo() override;
	// void exportarGrafo() override;
};

#endif
