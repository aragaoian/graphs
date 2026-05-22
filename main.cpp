#include <iostream>
#include <limits>
#include <map>
#include <vector>
#include <chrono>
#include "M1A/listGraph.h"
#include "M1A/matrixGraph.h"
#include "menu.h"

using namespace std;

// executar com
// bash -> g++ *.cpp M1A/*.cpp M2A/*.cpp M2B/*.cpp && ./a.out
// nushell -> g++ *.cpp M1A/*.cpp M2A/*.cpp M2B/*.cpp; ./a.out

int main(int argc, char *argv[])
{
    system("clear");

    cout << "Grafos" << endl;
    cout << "Professor: Rodrigo Lyra" << endl;
    cout << "Alunos: Ian Callegari Aragão, João Pedro Tonatto Fraga e Maria Eduarda Alves Martim" << endl;

    cin.get();

    map<int, string> fileOptionMap = {
        {1, "tests/direcionadoNaoPonderado.txt"},
        {2, "tests/direcionadoPonderado.txt"},
        {3, "tests/naoDirecionadoNaoPonderado.txt"},
        {4, "tests/naoDirecionadoPonderado.txt"},
        {5, "tests/espacoaereo.txt"},
        {6, "tests/slides.txt"},
        {7, "tests/slides_modificado.txt"},
        {8, "tests/Coloracao-r250-66-65.txt"},
        {9, "tests/AGM-50vertices50_Arestas.txt"},
        {10, "tests/coloringBruteForce.txt"}
    };

    while(true){
        system("clear");
        int fileUserOpt;

        cout << "Tipo do Grafo" << endl;
        cout << "1 - Direcionado Não Ponderado" << endl;
        cout << "2 - Direcionado Ponderado" << endl;
        cout << "3 - Não Direcionado Não Ponderado" << endl;
        cout << "4 - Não Direcionado Ponderado" << endl;
        cout << "5 - Espaço Aéreo" << endl;
        cout << "6 - Slides" << endl;
        cout << "7 - Slides Modificado" << endl;
        cout << "8 - Coloração" << endl;
        cout << "9 - AGM 50 Vértices" << endl;
        cout << "10 - Coloração pro Brute Force (V < 30)" << endl;
        cout << "0 - Encerrar" << endl;

        if (!(cin >> fileUserOpt)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (fileUserOpt > 10 || fileUserOpt < 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else {
            if (fileUserOpt == 0) {
                break;
            }

            auto fileIt = fileOptionMap.find(fileUserOpt);
            if (fileIt == fileOptionMap.end()) {
                continue;
            }

            const string selectedFile = fileIt->second;

            while(true){
                system("clear");
                int graphTypeUserOpt;
                
                cout << "Tipo de Representação do Grafo" << endl;
                cout << "1 - Lista" << endl;
                cout << "2 - Matriz" << endl;
                cout << "0 - Voltar" << endl;

                if (!(cin >> graphTypeUserOpt)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (graphTypeUserOpt > 2 || graphTypeUserOpt < 0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                } else {
                    if (graphTypeUserOpt == 0) {
                        break;
                    }

                    GrafoList grafoLista;
                    GrafoMatriz grafoMatriz;

                    switch(graphTypeUserOpt)
                    {
                    case 1: {
                        bool wasListCreated = grafoLista.criarGrafo(selectedFile);
                        if (!wasListCreated){
                            cout << "Não foi possível criar o grafo de lista" << endl;
                            wait_();
                            continue;
                        }

                        executeOpts(grafoLista);
                        break;
                    }
                    case 2: {
                        bool wasMatrixCreated = grafoMatriz.criarGrafo(selectedFile);
                        if (!wasMatrixCreated){
                            cout << "Não foi possível criar o grafo de matrix" << endl;
                            wait_();
                            continue;
                        }

                        executeOpts(grafoMatriz);
                        break;
                    }
                    default:
                        break;
                    }
                }
            }
        }
    }

    return 0;
}