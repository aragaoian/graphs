#include <vector>
#include <string>
#include "M1A/graphCreator.h"

void runTimedMST(
    Grafo &grafo,
    const std::vector<int> &vertices,
    const std::vector<int> &idToIndex,
    int raizIdx,
    bool isPrim,
    const std::string &funcName
);

void executeMST(Grafo &grafo);

void buildIndexMap(Grafo &grafo, std::vector<int> &vertices, std::vector<int> &idToIndex);