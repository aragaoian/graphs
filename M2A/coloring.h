#ifndef COLORING_H
#define COLORING_H

#include <vector>

// Força bruta 
int bruteForceColoring(std::vector<std::vector<int>>& adj, int V, std::vector<int>& color);

// Heurísticas
int greedyColoring(std::vector<std::vector<int>>& adj, int V, std::vector<int>& color);

int welshPowell(std::vector<std::vector<int>>& adj, int V, std::vector<int>& color);

int dsatur(std::vector<std::vector<int>>& adj, int V, std::vector<int>& color);

void printColoring(std::vector<int>& color, int V);

#endif