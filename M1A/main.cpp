#include <iostream>
#include <limits>
#include <map>
#include <vector>
#include "graphCreator.h"
#include "listGraph.h"
#include "matrixGraph.h"

using namespace std;

void printOrder(string titulo, vector<int> ordem)
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

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void wait_()
{
    cout << "\nPressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void executeOpts(Grafo &grafo)
{
    while (true)
    {
        system("clear");
        int operacao;

        cout << "Operacoes do Grafo" << endl;
        cout << "1 - Imprimir infos" << endl;
        cout << "2 - Imprimir grafo" << endl;
        cout << "3 - Inserir vertice" << endl;
        cout << "4 - Remover vertice" << endl;
        cout << "5 - Label do vertice" << endl;
        cout << "6 - Retornar vertices" << endl;
        cout << "7 - Retornar vizinhos" << endl;
        cout << "8 - Inserir aresta" << endl;
        cout << "9 - Remover aresta" << endl;
        cout << "10 - Existe aresta" << endl;
        cout << "11 - Peso da aresta" << endl;
        cout << "12 - Busca em largura" << endl;
        cout << "13 - Busca em profundidade" << endl;
        cout << "14 - Dijkstra" << endl;
        cout << "0 - Voltar" << endl;

        if (!(cin >> operacao))
        {
            clearInput();
            continue;
        }

        if (operacao < 0 || operacao > 14)
        {
            clearInput();
            continue;
        }

        if (operacao == 0)
        {
            clearInput();
            break;
        }

        system("clear");

        switch (operacao)
        {
        case 1:
            grafo.imprimeInfos();
            break;
        case 2:
            grafo.imprimeGrafo();
            break;
        case 3:
        {
            string label;
            cout << "Digite a label (vazio para sem label): ";
            cin >> ws;
            getline(cin, label);
            bool ok = grafo.inserirVertice(label);
            cout << (ok ? "Vertice inserido." : "Falha ao inserir vertice.") << endl;
            break;
        }
        case 4:
        {
            int indice;
            cout << "Indice do vertice: ";
            if (!(cin >> indice))
            {
                clearInput();
                break;
            }
            bool ok = grafo.removerVertice(indice);
            cout << (ok ? "Vertice removido." : "Falha ao remover vertice.") << endl;
            break;
        }
        case 5:
        {
            int indice;
            cout << "Indice do vertice: ";
            if (!(cin >> indice))
            {
                clearInput();
                break;
            }
            cout << "Label: " << grafo.labelVertice(indice) << endl;
            break;
        }
        case 6:
        {
            vector<int> vertices = grafo.retornarVertices();
            printOrder("Vertices: ", vertices);
            break;
        }
        case 7:
        {
            int vertice;
            cout << "Vertice de origem: ";
            if (!(cin >> vertice))
            {
                clearInput();
                break;
            }
            vector<int> vizinhos = grafo.retornarVizinhos(vertice);
            printOrder("Vizinhos: ", vizinhos);
            break;
        }
        case 8:
        {
            int origem, destino;
            float peso;
            cout << "Origem: ";
            if (!(cin >> origem))
            {
                clearInput();
                break;
            }
            cout << "Destino: ";
            if (!(cin >> destino))
            {
                clearInput();
                break;
            }
            cout << "Peso (use 1 para nao ponderado): ";
            if (!(cin >> peso))
            {
                clearInput();
                break;
            }
            bool ok = grafo.inserirAresta(origem, destino, peso);
            cout << (ok ? "Aresta inserida." : "Falha ao inserir aresta.") << endl;
            break;
        }
        case 9:
        {
            int origem, destino;
            cout << "Origem: ";
            if (!(cin >> origem))
            {
                clearInput();
                break;
            }
            cout << "Destino: ";
            if (!(cin >> destino))
            {
                clearInput();
                break;
            }
            bool ok = grafo.removerAresta(origem, destino);
            cout << (ok ? "Aresta removida." : "Falha ao remover aresta.") << endl;
            break;
        }
        case 10:
        {
            int origem, destino;
            cout << "Origem: ";
            if (!(cin >> origem))
            {
                clearInput();
                break;
            }
            cout << "Destino: ";
            if (!(cin >> destino))
            {
                clearInput();
                break;
            }
            cout << (grafo.existeAresta(origem, destino) ? "Existe aresta." : "Nao existe aresta.") << endl;
            break;
        }
        case 11:
        {
            int origem, destino;
            cout << "Origem: ";
            if (!(cin >> origem))
            {
                clearInput();
                break;
            }
            cout << "Destino: ";
            if (!(cin >> destino))
            {
                clearInput();
                break;
            }
            cout << "Peso: " << grafo.pesoAresta(origem, destino) << endl;
            break;
        }
        case 12:
        {
            int origem;
            cout << "Origem da busca em largura: ";
            if (!(cin >> origem))
            {
                clearInput();
                break;
            }
            vector<int> ordem = grafo.buscaLargura(origem);
            printOrder("Ordem BFS: ", ordem);
            break;
        }
        case 13:
        {
            int origem;
            cout << "Origem da busca em profundidade: ";
            if (!(cin >> origem))
            {
                clearInput();
                break;
            }
            vector<int> ordem = grafo.buscaProfundidade(origem);
            printOrder("Ordem DFS: ", ordem);
            break;
        }
        case 14:
        {
            int origem;
            cout << "Origem do Dijkstra: ";
            if (!(cin >> origem))
            {
                clearInput();
                break;
            }
            grafo.dijkstra(origem);
            break;
        }
        default:
            break;
        }

        wait_();
    }
}

int main(int argc, char *argv[])
{
    system("clear");

    cout << "M1 - Grafos" << endl;
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
        {7, "tests/slides_modificado.txt"}
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
        cout << "0 - Encerrar" << endl;

        if (!(cin >> fileUserOpt)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (fileUserOpt > 7 || fileUserOpt < 0) {
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