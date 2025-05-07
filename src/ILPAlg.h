#ifndef ILPALG_H
#define ILPALG_H

#include "truck.h"
#include "pallet.h"
#include <queue>
#include <vector>
#include "greedyAlg.h"
#include <climits>
using namespace std;

// node struct for bb tree
struct Node {
    int level;
    int upperBound; // best possible profit (fractional estimate)
    int cost; // actual profit of selected pallets
    int weight; //total weight of pallets in node
    vector<int> selectedPallets;

    // Max-heap based on upper bound (overload operator)
    bool operator<(const Node& other) const {
        return upperBound < other.upperBound;
    }
};

int getUpperBound(Node node, vector<Pallet>& pallets, int capacity);
vector<Pallet> ILPAlgorithm (Truck& truck, vector<Pallet>& pallet);

#endif