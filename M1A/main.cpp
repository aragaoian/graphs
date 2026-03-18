#include <iostream>
#include "listGraph.h"

using namespace std;

int main()
{
    GrafoList grafoLista;
    bool wasCreated = grafoLista.criarGrafo("tests/naoDirecionadoPonderado.txt");
    grafoLista.imprimeGrafo();
    grafoLista.imprimeInfos();
    grafoLista.inserirVertice("Teste");
    grafoLista.inserirAresta(5, 1, 18.0f);
    grafoLista.imprimeGrafo();
    grafoLista.imprimeInfos();
    cout << grafoLista.pesoAresta(5, 1) << endl;
    return 0;
}
