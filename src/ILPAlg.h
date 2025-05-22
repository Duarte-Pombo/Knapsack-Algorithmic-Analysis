#ifndef ILPALG_H
#define ILPALG_H
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include "pallet.h"
#include "truck.h"

using namespace std;
/**
 * @struct Node
 * @brief Represents a node in the decision tree for the branch and bound algorithm.
 *
 * Each node stores the current level in the tree, total weight and profit of selected pallets,
 * the number of pallets used, the sum of their IDs (for tie-breaking), the path taken, and a
 * bound on the maximum profit achievable from this node.
 */
struct Node {
    int level;
    int totalWeight;
    int totalProfit;
    int palletCount;
    int idSum;
    vector<int> path;
    double bound;
    /**
     * @brief Comparison operator for priority queue (max-heap).
     * @param other The other Node to compare against.
     * @return True if this node's bound is less than the other's (i.e., lower priority).
     */
    bool operator<(const Node& other) const {
        return bound < other.bound;
    }
};

/**
 * @brief Compares two nodes to determine which one is better based on profit, count, and ID sum.
 *
 * @param a First node.
 * @param b Second node.
 * @return true if node a is better than node b.
 */
bool better(const Node& a, const Node& b);
/**
 * @brief Calculates the upper bound (optimistic profit estimate) for a node.
 *
 * @param node Current node.
 * @param truck The truck being loaded.
 * @param pallets List of all pallets.
 * @param n Total number of pallets.
 * @return Upper bound of profit starting from this node.
 */
double bound(const Node& node, const Truck& truck, const vector<Pallet>& pallets, int n);
/**
 * @brief Solves the 0/1 knapsack problem using a branch and bound algorithm
 *        tailored for truck loading with pallet constraints.
 *
 * Pallets are selected to maximize profit while respecting the truck’s weight limit.
 * Ties are broken by fewer pallets and lower ID sum.
 *
 * @param truck The truck object with a max weight limit.
 * @param pallets The list of available pallets with weight and value.
 * @return A vector of selected pallets forming the optimal solution.
 *
 * @complexity O(2^n) in the worst case (due to branching), but pruning and bounding
 * significantly reduce this in practice. Sorting takes O(n log n).
 */
vector<Pallet> ILPAlgorithm(Truck& truck, vector<Pallet>& pallets);

#endif