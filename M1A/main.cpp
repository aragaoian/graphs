#include <iostream>
#include "listGraph.h"

using namespace std;

int main()
{
    GrafoList grafoLista;
    bool wasCreated = grafoLista.criarGrafo("tests/naoPonderado.txt");
    grafoLista.imprimeGrafo();
    vector<int> neighboors = grafoLista.retornarVizinhos(0);
    for(int n: neighboors){
        cout << n << endl;
    }
    return 0;
}
