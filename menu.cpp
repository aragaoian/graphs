#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include "menu.h"
#include "M1A/graphCreator.h"
#include "M1A/listGraph.h"
#include "M1A/matrixGraph.h"
#include "M1B/timedTests.h"

void printOrder(std::string titulo, std::vector<int> ordem)
{
    std::cout << titulo;
    for (int i = 0; i < ordem.size(); i++)
    {
        std::cout << ordem[i];
        if (i + 1 < ordem.size())
        {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void wait_()
{
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void executeOpts(Grafo &grafo)
{
    while (true)
    {
        system("clear");
        int opt;

        std::cout << "Operacoes do Grafo" << std::endl;
        std::cout << "1 - Imprimir infos" << std::endl;
        std::cout << "2 - Imprimir grafo" << std::endl;
        std::cout << "3 - Inserir vertice" << std::endl;
        std::cout << "4 - Remover vertice" << std::endl;
        std::cout << "5 - Label do vertice" << std::endl;
        std::cout << "6 - Retornar vertices" << std::endl;
        std::cout << "7 - Retornar vizinhos" << std::endl;
        std::cout << "8 - Inserir aresta" << std::endl;
        std::cout << "9 - Remover aresta" << std::endl;
        std::cout << "10 - Existe aresta" << std::endl;
        std::cout << "11 - Peso da aresta" << std::endl;
        std::cout << "12 - Busca em largura" << std::endl;
        std::cout << "13 - Busca em profundidade" << std::endl;
        std::cout << "14 - Dijkstra" << std::endl;
        std::cout << "15 - Coloracao de Grafos" << std::endl;
        std::cout << "0 - Voltar" << std::endl;

        if (!(std::cin >> opt))
        {
            clearInput();
            continue;
        }

        if (opt < 0 || opt > 15)
        {
            clearInput();
            continue;
        }

        if (opt == 0)
        {
            clearInput();
            break;
        }

        system("clear");

        switch (opt)
        {
        case 1:
            grafo.imprimeInfos();
            break;
        case 2:
            grafo.imprimeGrafo();
            break;
        case 3:
        {
            std::string label;
            std::cout << "Digite a label (vazio para sem label): ";
            std::cin >> std::ws;
            getline(std::cin, label);
            bool ok = grafo.inserirVertice(label);
            std::cout << (ok ? "Vertice inserido." : "Falha ao inserir vertice.") << std::endl;
            break;
        }
        case 4:
        {
            int indice;
            std::cout << "Indice do vertice: ";
            if (!(std::cin >> indice))
            {
                clearInput();
                break;
            }
            bool ok = grafo.removerVertice(indice);
            std::cout << (ok ? "Vertice removido." : "Falha ao remover vertice.") << std::endl;
            break;
        }
        case 5:
        {
            int indice;
            std::cout << "Indice do vertice: ";
            if (!(std::cin >> indice))
            {
                clearInput();
                break;
            }
            std::cout << "Label: " << grafo.labelVertice(indice) << std::endl;
            break;
        }
        case 6:
        {
            std::vector<int> vertices = grafo.retornarVertices();
            printOrder("Vertices: ", vertices);
            break;
        }
        case 7:
        {
            int vertice;
            std::cout << "Vertice de origem: ";
            if (!(std::cin >> vertice))
            {
                clearInput();
                break;
            }
            std::vector<int> vizinhos = grafo.retornarVizinhos(vertice);
            printOrder("Vizinhos: ", vizinhos);
            break;
        }
        case 8:
        {
            int origem, destino;
            float peso;
            std::cout << "Origem: ";
            if (!(std::cin >> origem))
            {
                clearInput();
                break;
            }
            std::cout << "Destino: ";
            if (!(std::cin >> destino))
            {
                clearInput();
                break;
            }
            std::cout << "Peso (use 1 para nao ponderado): ";
            if (!(std::cin >> peso))
            {
                clearInput();
                break;
            }
            bool ok = grafo.inserirAresta(origem, destino, peso);
            std::cout << (ok ? "Aresta inserida." : "Falha ao inserir aresta.") << std::endl;
            break;
        }
        case 9:
        {
            int origem, destino;
            std::cout << "Origem: ";
            if (!(std::cin >> origem))
            {
                clearInput();
                break;
            }
            std::cout << "Destino: ";
            if (!(std::cin >> destino))
            {
                clearInput();
                break;
            }
            bool ok = grafo.removerAresta(origem, destino);
            std::cout << (ok ? "Aresta removida." : "Falha ao remover aresta.") << std::endl;
            break;
        }
        case 10:
        {
            int origem, destino;
            std::cout << "Origem: ";
            if (!(std::cin >> origem))
            {
                clearInput();
                break;
            }
            std::cout << "Destino: ";
            if (!(std::cin >> destino))
            {
                clearInput();
                break;
            }
            std::cout << (grafo.existeAresta(origem, destino) ? "Existe aresta." : "Nao existe aresta.") << std::endl;
            break;
        }
        case 11:
        {
            int origem, destino;
            std::cout << "Origem: ";
            if (!(std::cin >> origem))
            {
                clearInput();
                break;
            }
            std::cout << "Destino: ";
            if (!(std::cin >> destino))
            {
                clearInput();
                break;
            }
            std::cout << "Peso: " << grafo.pesoAresta(origem, destino) << std::endl;
            break;
        }
        case 12:
        {
            int origem;
            std::cout << "Origem da busca em largura: ";
            if (!(std::cin >> origem))
            {
                clearInput();
                break;
            }
            std::vector<int> ordem = grafo.buscaLargura(origem);
            printOrder("Ordem BFS: ", ordem);
            break;
        }
        case 13:
        {
            int origem;
            std::cout << "Origem da busca em profundidade: ";
            if (!(std::cin >> origem))
            {
                clearInput();
                break;
            }
            std::vector<int> ordem = grafo.buscaProfundidade(origem);
            printOrder("Ordem DFS: ", ordem);
            break;
        }
        case 14:
        {
            int origem;
            std::cout << "Origem do Dijkstra: ";
            if (!(std::cin >> origem))
            {
                clearInput();
                break;
            }
            grafo.dijkstra(origem);
            break;
        }
        case 15:
        {
            executeTimedTests(grafo);
            break;
        }
        default:
            break;
        }

        wait_();
    }
}