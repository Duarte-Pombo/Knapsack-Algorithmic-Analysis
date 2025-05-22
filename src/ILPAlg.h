#ifndef ILPALG_H
#define ILPALG_H
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include "pallet.h"
#include "truck.h"

using namespace std;

struct Node {
    int level;
    int totalWeight;
    int totalProfit;
    int palletCount;
    int idSum;
    vector<int> path;
    double bound;
    // overload operator
    bool operator<(const Node& other) const {
        return bound < other.bound;
    }
};

// Function declarations
bool better(const Node& a, const Node& b);
double bound(const Node& node, const Truck& truck, const vector<Pallet>& pallets, int n);
vector<Pallet> ILPAlgorithm(Truck& truck, vector<Pallet>& pallets);

#endif