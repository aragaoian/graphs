#include <iostream>
#include "listGraph.h"

using namespace std;

int main()
{
    GrafoList grafoLista;
    bool wasCreated = grafoLista.criarGrafo("tests/naoDirecionadoPonderado.txt");
    grafoLista.imprimeGrafo();
    grafoLista.imprimeInfos();
    return 0;
}
