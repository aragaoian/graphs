#include "coloring.h"
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

// =======================
// FUNÇÕES AUXILIARES
// =======================

bool isSafe(int v, vector<int>& color, int c, vector<vector<int>>& adj) {
    for (int u : adj[v]) {
        if (color[u] == c) return false;
    }
    return true;
}

bool backtracking(int v, int k, vector<int>& color, vector<vector<int>>& adj, int V) {
    if (v == V) return true;

    for (int c = 0; c < k; c++) {
        if (isSafe(v, color, c, adj)) {
            color[v] = c;
            if (backtracking(v + 1, k, color, adj, V))
                return true;
            color[v] = -1;
        }
    }
    return false;
}

// =======================
// FORÇA BRUTA
// =======================

int bruteForceColoring(vector<vector<int>>& adj, int V, vector<int>& result) {
    for (int k = 2; k <= V; k++) {
        vector<int> color(V, -1);

        if (backtracking(0, k, color, adj, V)) {
            result = color;
            return k;
        }
    }
    return V;
}

// =======================
// GULOSO SIMPLES
// =======================

int greedyColoring(vector<vector<int>>& adj, int V, vector<int>& color) {
    color.assign(V, -1);
    color[0] = 0;

    for (int u = 1; u < V; u++) {
        vector<bool> used(V, false);

        for (int v : adj[u]) {
            if (color[v] != -1)
                used[color[v]] = true;
        }

        int c;
        for (c = 0; c < V; c++) {
            if (!used[c]) break;
        }

        color[u] = c;
    }

    return *max_element(color.begin(), color.end()) + 1;
}

// =======================
// WELSH-POWELL
// =======================

int welshPowell(vector<vector<int>>& adj, int V, vector<int>& color) {
    vector<pair<int,int>> degree;

    for (int i = 0; i < V; i++)
        degree.push_back({adj[i].size(), i});

    sort(degree.rbegin(), degree.rend());

    color.assign(V, -1);
    int currentColor = 0;

    for (auto &p : degree) {
        int u = p.second;

        if (color[u] == -1) {
            color[u] = currentColor;

            for (auto &p2 : degree) {
                int v = p2.second;

                if (color[v] == -1) {
                    bool canColor = true;

                    for (int neigh : adj[v]) {
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

// =======================
// DSATUR
// =======================

int dsatur(vector<vector<int>>& adj, int V, vector<int>& color) {
    color.assign(V, -1);

    vector<int> degree(V);
    for (int i = 0; i < V; i++)
        degree[i] = adj[i].size();

    vector<set<int>> sat(V);

    for (int i = 0; i < V; i++) {
        int u = -1;

        for (int j = 0; j < V; j++) {
            if (color[j] == -1) {
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

        int c;
        for (c = 0; c < V; c++) {
            if (!used[c]) break;
        }

        color[u] = c;

        for (int v : adj[u]) {
            if (color[v] == -1)
                sat[v].insert(c);
        }
    }

    return *max_element(color.begin(), color.end()) + 1;
}

// =======================
// PRINT
// =======================

void printColoring(vector<int>& color, int V) {
    if (V < 10) {
        for (int i = 0; i < V; i++) {
            cout << "Vertice " << i << " -> Cor " << color[i] << endl;
        }
    }
}