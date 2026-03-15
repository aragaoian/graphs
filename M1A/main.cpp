#include <iostream>
#include "listGraph.h"

using namespace std;

int main()
{
    GrafoList grafoLista;
    bool wasCreated = grafoLista.criarGrafo("tests/naoPonderado.txt");
    cout << wasCreated << endl;
    grafoLista.imprimeGrafo();
    cout << endl;
    grafoLista.inserirVertice();
    grafoLista.inserirVertice("Ian");
    grafoLista.imprimeGrafo();
    
    return 0;
}
