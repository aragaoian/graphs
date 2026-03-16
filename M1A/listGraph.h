#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <string>
#include <map>
#include <vector>
#include "graphCreator.h"

class GrafoList : public Grafo {
private:
	std::map<int, vector<Aresta>> grafo;
	std::map<int, string> labels;
	virtual int indexMaximo();
	
public:
	bool criarGrafo(std::string path = "") override;

    bool inserirVertice(string label = "") override;
    bool removerVertice(int indice) override;
	string labelVertice(int indice) override;
	vector<int> retornarVizinhos(int vertice) override;

	void imprimeGrafo() override;
};

#endif
