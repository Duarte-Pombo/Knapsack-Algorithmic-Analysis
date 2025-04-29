#ifndef ILPALG_H
#define ILPALG_H

#include <vector>
#include <iostream>
#include "truck.h"
#include "pallet.h"
#include "greedyAlg.h" // using the sorting alg function from this
#include <queue>
#include <algorithm>

using namespace std;

// node struct for the branch and bound tree
struct Node {
    int nodeLevel; // depth of the node in the decision tree
    int nodeProfit;
    int nodeWeight;
    double bound; // maximum potential profits

    vector<bool> palletsInNode;

    bool operator < (const Node& rhs) const {
        return bound > rhs.bound; // overloader to compare the nodes in pqueue by their bound
    }
};

double bound(const Node& node, const vector<Pallet>& pallets, int capacity);
vector<Pallet> ILPAlgorithm (Truck& truck, vector<Pallet>& pallet);

#endif