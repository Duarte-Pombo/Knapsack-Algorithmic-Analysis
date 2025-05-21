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

/**
 * @brief Calculates the upper bound for a node in the branch-and-bound tree.
 * @param node Current node.
 * @param pallets List of pallets.
 * @param capacity Maximum weight capacity of the truck.
 * @return Upper bound for the node.
 * @complexity O(n), where n is the number of pallets.
 */
int getUpperBound(Node node, vector<Pallet>& pallets, int capacity);

/**
 * @brief Solves the pallet selection problem using Integer Linear Programming (ILP).
 * @param truck Truck object.
 * @param pallet List of pallets.
 * @return Vector of selected pallets.
 * @complexity O(2^n), where n is the number of pallets (worst case for branch-and-bound).
 */
vector<Pallet> ILPAlgorithm (Truck& truck, vector<Pallet>& pallet);

#endif