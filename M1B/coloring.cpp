#include "coloring.h"
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

// NOTE
// verificar se é possivel colorir o vertice v com a cor c
// caso exista a cor em algum adjacente, retorna false
// caso contrário, retorna true
bool verifyAdjcentsColors(int v, vector<int>& color, int c, vector<vector<int>>& adj) {
    for (int u : adj[v]) {
        if (color[u] == c) return false;
    }
    return true;
}


bool backtracking(int v, int k, vector<int>& color, vector<vector<int>>& adj, int V) {
    /*
    Tenta todas as combinações de cores possíveis para os vértices
    para k >= 2.

    * Args:
    int v -> vértices index
    int k -> total de cores
    vector<int>& color -> vetor de cores
    vector<vector<int>>& adj -> vetor de adjacência
    int V -> total de vértices
    */
    if (v == V) return true;
   
    for (int c = 0; c < k; c++) {
        if (verifyAdjcentsColors(v, color, c, adj)) {
            color[v] = c;
            if (backtracking(v + 1, k, color, adj, V))
                return true;
            color[v] = -1;
        }
    }
    return false;
}


int bruteForceColoring(vector<vector<int>>& adj, int V, vector<int>& result) {
    /*
    Retorna a quantidade minima de cores para colorir o grafo (sem que os)
    vértices adjacentes tenham cores iguais.
    
    O pior caso é cada vértice ter uma cor distinta.
    */
    for (int k = 2; k <= V; k++) {
        vector<int> color(V, -1);
        if (backtracking(0, k, color, adj, V)) {
            result = color;
            return k; // quantidade mínima
        }
    }
    return V;
}


int greedyColoring(vector<vector<int>>& adj, int V, vector<int>& color) {
    /*Colore na ordem dos vértices, usando sempre a menor cor como primeira escolha.*/
    color.assign(V, -1);

    color[0] = 0;

    for (int u = 1; u < V; u++) {
        vector<bool> used(V, false);

        for (int v : adj[u]) {
            // Se o adjacente já tem uma cor
            // marca essa cor como usada
            if (color[v] != -1)
                used[color[v]] = true;
        }

        // Procura a cor que não foi usada
        // pelos adjacentes
        int c;
        for (c = 0; c < V; c++) {
            if (!used[c]) break;
        }

        color[u] = c;
    }

    // Retorna o número de cores usadas,
    // que é a maior cor atribuída + 1
    return *max_element(color.begin(), color.end()) + 1;
}


int welshPowell(vector<vector<int>>& adj, int V, vector<int>& color) {
    /*Colorir os grau de ordem DESC, em rodadas com a mesma cor.*/
    // pair = grau e index
    vector<pair<int,int>> degree;

    for (int i = 0; i < V; i++)
        degree.push_back({adj[i].size(), i});

    // NOTE
    // vértices com maior grau são coloridos primeiro
    sort(degree.rbegin(), degree.rend());

    color.assign(V, -1);

    int currentColor = 0;

    for (auto &p : degree) {
        int u = p.second;

        if (color[u] == -1) {
            color[u] = currentColor;

            for (auto &p2 : degree) {
                int v = p2.second;

                // O vértice v não pode ser adjacente a u e 
                // não pode estar colorido
                if (color[v] == -1) {
                    bool canColor = true;
                    for (int neigh : adj[v]) {
                        // Verifica os vizinhos se tem a cor atual, caso tenha,
                        // não pode colorir v com a cor atual
                        if (color[neigh] == currentColor) {
                            canColor = false;
                            break;
                        }
                    }

                    if (canColor)
                        color[v] = currentColor;
                }
            }      
            currentColor++;
        }
    }

    return currentColor;
}

int dsatur(vector<vector<int>>& adj, int V, vector<int>& color) {
    color.assign(V, -1);

    vector<int> degree(V);
    for (int i = 0; i < V; i++)
        degree[i] = adj[i].size();

    // Vetor de saturação, onde cada posição representa 
    // o número de cores distintas nos vizinhos do vértice correspondente
    vector<set<int>> sat(V);

    for (int i = 0; i < V; i++) {
        int u = -1;

        for (int j = 0; j < V; j++) {
            if (color[j] == -1) {
                // Trocar de canditado caso:
                // 1. Saturação de J maior que U
                // 2. OU ambos podem ter a mesma saturação, mas 
                // o grau de J é maior que de U.
                if (u == -1 ||
                    sat[j].size() > sat[u].size() ||
                    (sat[j].size() == sat[u].size() && degree[j] > degree[u])) {
                    u = j;
                }
            }
        }

        vector<bool> used(V, false);
        for (int v : adj[u]) {
            if (color[v] != -1)
                used[color[v]] = true;
        }

        // Procura a proxima cor disponível
        int c;
        for (c = 0; c < V; c++) {
            if (!used[c]) break;
        }
        color[u] = c;

        //atualiza a saturação dos vizinhos de u, adicionando a cor c ao conjunto de cores distintas dos vizinhos
        for (int v : adj[u]) {
            if (color[v] == -1)
                sat[v].insert(c);
        }
    }

    return *max_element(color.begin(), color.end()) + 1;
}

void printColoring(vector<int>& color, int V) {
    if(V > 10) return;
    for (int i = 0; i < V; i++) {
        cout << "Vertice " << i << " -> Cor " << color[i] << endl;
    }
}