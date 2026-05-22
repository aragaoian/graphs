#ifndef TIMEDTESTS_H
#define TIMEDTESTS_H

#include <vector>
#include <string>
#include "../M1A/graphCreator.h"

void timedTests(std::vector<std::vector<int>> &adj, int V, std::vector<int> &color, int (func)(std::vector<std::vector<int>> &, int, std::vector<int> &), Grafo &grafo, std::string funcName);

void executeTimedTests(Grafo &grafo);

#endif