#ifndef ILPALG_H
#define ILPALG_H

#include "truck.h"
#include "pallet.h"
#include <queue>
#include <vector>
#include "greedyAlg.h"
#include <climits>
#include <math.h>
#include <limits>

using namespace std;

// Node struct for branch and bound tree
struct Node {
    int level;              // Current level in the decision tree
    int cost;               // Total profit of selected pallets
    int weight;             // Total weight of selected pallets
    int upperBound;         // Upper bound estimate for this branch
    vector<int> selectedPallets;  // Track which pallets are selected
    int palletCount;        // Number of pallets selected in this node
    long long idSum;        // Sum of IDs of selected pallets

    // Override comparison operator for priority queue (max heap)
    bool operator<(const Node& other) const {
        // Primary criterion: Upper bound (higher is better)
        if (upperBound != other.upperBound)
            return upperBound < other.upperBound;

        // Secondary criterion: Actual cost/profit (higher is better)
        if (cost != other.cost)
            return cost < other.cost;

        // Tertiary criterion: Pallet count (lower is better)
        if (palletCount != other.palletCount)
            return palletCount > other.palletCount;

        // Quaternary criterion: ID sum (lower is better)
        return idSum > other.idSum;
    }
};

// Function declarations
int upperBound(const Node& node, const vector<Pallet>& pallets, int capacity);
vector<Pallet> ILPAlgorithm(Truck& truck, vector<Pallet>& pallets);

#endif