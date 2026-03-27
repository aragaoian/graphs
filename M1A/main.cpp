#include <iostream>
#include <vector>
#include "listGraph.h"
#include "matrixGraph.h"

using namespace std;

void imprimeOrdem(string titulo, vector<int> ordem)
{
    cout << titulo;
    for (int i = 0; i < ordem.size(); i++)
    {
        cout << ordem[i];
        if (i + 1 < ordem.size())
        {
            cout << " -> ";
        }
    }
    cout << endl;
}

int main()
{
    cout << "M1 - GRAFOS" << endl;

    GrafoList grafoLista;
    GrafoMatriz grafoMatriz;

    bool wasListCreated = grafoLista.criarGrafo("tests/naoDirecionadoPonderado.txt");
    bool wasMatrixCreated = grafoMatriz.criarGrafo("tests/naoDirecionadoPonderado.txt");

    if (!wasListCreated || !wasMatrixCreated)
    {
        cout << "Nao foi possivel criar os grafos." << endl;
        return 1;
    }

    // cout << "Lista de adjacencia" << endl;
    // grafoLista.imprimeGrafo();
    // grafoLista.imprimeInfos();
    // imprimeOrdem("BFS: ", grafoLista.buscaLargura(0));
    // imprimeOrdem("DFS: ", grafoLista.buscaProfundidade(0));
    // grafoLista.dijkstra(0);

    cout << endl
         << "Matriz de adjacencia" << endl;
    grafoMatriz.imprimeGrafo();
    // grafoMatriz.imprimeInfos();
    // imprimeOrdem("BFS: ", grafoMatriz.buscaLargura(0));
    // imprimeOrdem("DFS: ", grafoMatriz.buscaProfundidade(0));
    // grafoMatriz.dijkstra(0);

    return 0;
}