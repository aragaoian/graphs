#ifndef COLORING_H
#define COLORING_H

#include <vector>

using namespace std;

// Força bruta 
int bruteForceColoring(vector<vector<int>>& adj, int V, vector<int>& color);

// Heurísticas
int greedyColoring(vector<vector<int>>& adj, int V, vector<int>& color);

int welshPowell(vector<vector<int>>& adj, int V, vector<int>& color);

int dsatur(vector<vector<int>>& adj, int V, vector<int>& color);

// Impressão
void printColoring(vector<int>& color, int V);

#endif