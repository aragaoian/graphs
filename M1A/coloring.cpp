#include "coloring.h"
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

//verificar se é possivel colorir o vertice v com a cor c
//caso exista a cor em algum adjacente, retorna false
//caso contrário, retorna true
bool isSafe(int v, vector<int>& color, int c, vector<vector<int>>& adj) {
    for (int u : adj[v]) {
        if (color[u] == c) return false;
    }
    return true;
}

//tenta todas as combinações de cores para colorir o grafo usando no máximo k cores

bool backtracking(int v, int k, vector<int>& color, vector<vector<int>>& adj, int V) {
    //caso todos os vértices estejam coloridos, retorna true
    if (v == V) return true;

    //para cada vertice, tenta colorir com cada cor possível    
    for (int c = 0; c < k; c++) {
        //verificar se algum adjacente já tem a cor c
        if (isSafe(v, color, c, adj)) {
            //atribui a cor c ao vértice v
            color[v] = c;
            //tenta colorir o próximo vértice
            if (backtracking(v + 1, k, color, adj, V))
                //se conseguiu colorir o próximo vértice, retorna true
                return true;
            //se não conseguiu colorir o próximo vértice, remove a cor do vértice v e tenta a próxima cor
            color[v] = -1;
        }
    }
    return false;
}

// Força Bruta

int bruteForceColoring(vector<vector<int>>& adj, int V, vector<int>& result) {
    // Tenta colorir o grafo usando de 1 a V cores (no pior caso, cada vértice tem uma cor diferente)
    for (int k = 2; k <= V; k++) {
        //inicializa todos sem cor
        vector<int> color(V, -1);

        //caso seja possível colorir o grafo com k cores, salva o resultado e retorna o número de cores usadas
        if (backtracking(0, k, color, adj, V)) {
            result = color;
            //quantidade minima de cores necessárias para colorir o grafo
            return k;
        }
    }
    //caso não seja possível colorir o grafo com V cores, retorna V (o pior caso é cada vértice ter uma cor diferente)
    return V;
}

// Guloso Simples

int greedyColoring(vector<vector<int>>& adj, int V, vector<int>& color) {
    //inicializa todos sem cor
    color.assign(V, -1);
    //primeiro vertice recebe a primeira cor
    color[0] = 0;

    for (int u = 1; u < V; u++) {
        //marca as cores dos adjacentes como usadas
        vector<bool> used(V, false);

        //para cada adjacente do vértice u, marca a cor como usada
        for (int v : adj[u]) {
            //se o adjacente já tem uma cor, marca essa cor como usada
            if (color[v] != -1)
                used[color[v]] = true;
        }

        //procura a proxima cor disponível (a menor cor que não foi usada pelos adjacentes)
        int c;
        for (c = 0; c < V; c++) {
            if (!used[c]) break;
        }

        //atribui a cor c ao vértice u
        color[u] = c;
    }

    //retorna o número de cores usadas, que é a maior cor atribuída + 1 (pois as cores começam do 0)
    return *max_element(color.begin(), color.end()) + 1;
}

// Welsh-Powell

int welshPowell(vector<vector<int>>& adj, int V, vector<int>& color) {
    vector<pair<int,int>> degree;

    //guarda o grau de cada vértice junto com seu índice
    for (int i = 0; i < V; i++)
        degree.push_back({adj[i].size(), i});

    //organiza de forma decrescente pelo grau, para que os vértices com maior grau sejam coloridos primeiro
    sort(degree.rbegin(), degree.rend());

    //inicializa todos sem cor
    color.assign(V, -1);
    //inicializa na cor 0
    int currentColor = 0;

    for (auto &p : degree) {
        int u = p.second;

        if (color[u] == -1) {
            //atribui a cor atual ao vértice u
            color[u] = currentColor;

            for (auto &p2 : degree) {
                //para cada vértice v, verifica se ele é adjacente a u e se pode ser colorido com a cor atual
                int v = p2.second;

                //caso a cor do vertice v seja -1 (ou seja, ainda não foi colorido) e v não seja adjacente a u
                if (color[v] == -1) {
                    //assume que pode colorir o vértice v com a cor currentColor
                    bool canColor = true;

                    //tenta colorir v com a cor atual
                    for (int neigh : adj[v]) {
                        //verifica os vizinhos se tem a cor atual, caso tenha, não pode colorir v com a cor atual
                        if (color[neigh] == currentColor) {
                            canColor = false;
                            break;
                        }
                    }

                    //caso seja possível colorir v com a cor atual, atribui a cor currentColor ao vértice v
                    if (canColor)
                        color[v] = currentColor;
                }
            }
            //incrementa a cor para o próximo vértice que ainda não foi colorido        
            currentColor++;
        }
    }

    return currentColor;
}

// Dsatur

int dsatur(vector<vector<int>>& adj, int V, vector<int>& color) {
    //atribui a cor -1 para todos os vértices, indicando que estão sem cor
    color.assign(V, -1);

   //cria o vetor de grau e conta os vizinhos
    vector<int> degree(V);
    for (int i = 0; i < V; i++)
        degree[i] = adj[i].size();

    //vetor de saturação, onde cada posição representa o número de cores distintas nos vizinhos do vértice correspondente
    vector<set<int>> sat(V);

    //para cada vértice
    for (int i = 0; i < V; i++) {
        //vértice atual -> melhor candidato para ser colorido
        int u = -1;

        for (int j = 0; j < V; j++) {
            //apenas considera os vértices que ainda não foram coloridos
            if (color[j] == -1) {
                //caso o vértice atual seja -1, 
                //a saturação do vértice j seja maior que a saturação do vértice u, 
                //ou caso as saturações sejam iguais e o grau do vértice j seja maior que o grau do vértice u, 
                //então o vértice j se torna o novo candidato u
                if (u == -1 ||
                    sat[j].size() > sat[u].size() ||
                    (sat[j].size() == sat[u].size() && degree[j] > degree[u])) {
                    u = j;
                }
            }
        }

        //marca as cores dos adjacentes como usadas
        vector<bool> used(V, false);
        //para cada adjacente do vértice u, marca a cor como usada
        for (int v : adj[u]) {
            //se o adjacente já tem uma cor, marca essa cor como usada
            if (color[v] != -1)
                used[color[v]] = true;
        }

        //procura a proxima cor disponível (a menor cor que não foi usada pelos adjacentes)
        int c;
        for (c = 0; c < V; c++) {
            //se a cor c não foi usada pelos adjacentes, pode ser atribuída ao vértice u
            if (!used[c]) break;
        }

        //atribui a cor c ao vértice u
        color[u] = c;

        //atualiza a saturação dos vizinhos de u, adicionando a cor c ao conjunto de cores distintas dos vizinhos
        for (int v : adj[u]) {
            if (color[v] == -1)
                sat[v].insert(c);
        }
    }

    //retorna o número de cores usadas, que é a maior cor atribuída + 1 (pois as cores começam do 0)
    return *max_element(color.begin(), color.end()) + 1;
}

void printColoring(vector<int>& color, int V) {
    if (V < 10) {
        for (int i = 0; i < V; i++) {
            cout << "Vertice " << i << " -> Cor " << color[i] << endl;
        }
    }
}