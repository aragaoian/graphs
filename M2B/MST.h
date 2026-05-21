#ifndef MST_H
#define MST_H

#include "../M1A/graphCreator.h"
#include <vector>
using namespace std;

struct ArestaMST {
    int origem;
    int destino;
    float peso;
};

vector<ArestaMST> prim(Grafo &grafo, const vector<int> &vertices, const vector<int> &idToIndex,int raizIdx);

vector<ArestaMST> kruskal(Grafo &grafo, const vector<int> &vertices,const vector<int> &idToIndex);

void executeMST(Grafo &grafo);

#endif