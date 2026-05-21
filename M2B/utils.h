#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <algorithm>
#include <numeric>

struct UnionFind {
    std::vector<int> father, rank_;

    // Inicializa n vertices
    // cada um tem sua própria árvore
    UnionFind(int n) : father(n), rank_(n, 0) {
        iota(father.begin(), father.end(), 0);
    }

    // Encontra o representante da
    // arvore do vertice x (com path compression)
    int find(int x) {
        if (father[x] != x) father[x] = find(father[x]);
        return father[x];
    }

    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);

        if (rx == ry) return false;

        if (rank_[rx] < rank_[ry]){
            std::swap(rx, ry);
        }
        father[ry] = rx;

        if (rank_[rx] == rank_[ry]){
            rank_[rx]++;
        }
        return true;
    }
};