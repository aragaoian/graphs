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

public:
	bool criarGrafo(std::string path = "") override;
	void imprimeGrafo() override;
    bool inserirVertice(string label) override;
    bool removerVertice(int indice) override;
    virtual int indexMaximo();
};

#endif
