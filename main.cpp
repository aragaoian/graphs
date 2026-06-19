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
// bash -> g++ *.cpp M1A/*.cpp M2A/*.cpp M2B/*.cpp M3/*.cpp && ./a.out
// nushell -> g++ *.cpp M1A/*.cpp M2A/*.cpp M2B/*.cpp M3/*.cpp; ./a.out

int main(int argc, char *argv[])
{
    clearScreen();

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
        {10, "tests/coloringBruteForce.txt"},
        {11, "tests/1000vertices25%Arestas.txt"},
        {12, "tests/500vertices100%Arestas.txt"},
        {13, "tests/500vertices25%Arestas.txt"},
        {14, "tests/500vertices50%Arestas.txt"},
        {15, "tests/50vertices100%Arestas.txt"},
        {16, "tests/50vertices25%Arestas.txt"},
        {17, "tests/50vertices50%Arestas.txt"},
        {18, "tests/C4000-260-X.txt"},
        {19, "tests/k33.txt"},
        {20, "tests/k5.txt"},
        {21, "tests/kquase5.txt"},
        {22, "tests/r1000-234-234.txt"},
        {23, "tests/r250-66-65.txt"},
        {24, "tests/test.txt"},
        {25, "tests/fluxoMaximo.txt"}
    };

    while(true){
        clearScreen();
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
        cout << "11 - 1000 vertices 25% Arestas" << endl;
        cout << "12 - 500 vertices 100% Arestas" << endl;
        cout << "13 - 500 vertices 25% Arestas" << endl;
        cout << "14 - 500 vertices 50% Arestas" << endl;
        cout << "15 - 50 vertices 100% Arestas" << endl;
        cout << "16 - 50 vertices 25% Arestas" << endl;
        cout << "17 - 50 vertices 50% Arestas" << endl;
        cout << "18 - C4000-260-X" << endl;
        cout << "19 - K3,3" << endl;
        cout << "20 - K5" << endl;
        cout << "21 - K quase 5" << endl;
        cout << "22 - r1000-234-234" << endl;
        cout << "23 - r250-66-65" << endl;
        cout << "24 - test.txt" << endl;
        cout << "25 - Fluxo Maximo" << endl;
        cout << "0 - Encerrar" << endl;

        if (!(cin >> fileUserOpt)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (fileUserOpt > 25 || fileUserOpt < 0) {
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
                clearScreen();
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
