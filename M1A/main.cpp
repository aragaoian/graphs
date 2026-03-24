#include <iostream>
#include <filesystem>
#include "listGraph.h"

using namespace std;

const string path = filesystem::current_path().string();

int main()
{
    GrafoList grafoLista;
    bool wasCreated = grafoLista.criarGrafo(path + "/tests/directed_weighted_80.txt");
    return 0;
}