// source https://www.youtube.com/watch?v=yV1d-b_NeK8&t=133s&ab_channel=AbdulBari

#include "ILPAlg.h"

#include <math.h>

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

// fractional upper bound
int upperBound(const Node& node, const vector<Pallet>& pallets, int capacity) {
    if (node.weight >= capacity) {
        return 0;
    }

    int bound = node.cost;
    int remainWeight = capacity - node.weight;
    int i = node.level + 1;

    // greedily add pallets until capacity full
    while (i < pallets.size() && pallets[i].getPalletWeight() <= remainWeight) {
        bound += pallets[i].getPalletValue();
        remainWeight -= pallets[i].getPalletWeight();
        i++;
    }

    // add fration of next item if space remains
    if (i < pallets.size()) {
        bound += (pallets[i].getPalletValue() * remainWeight) / pallets[i].getPalletWeight();
    }

    return bound;
}

// Branch and Bound ILP algorithm
vector<Pallet> ILPAlgorithm(Truck& truck, vector<Pallet>& pallets) {
    int n = pallets.size();
    int capacity = truck.getMaxWeight();
    /*
     * Change made from the video, by sorting we can increase the likelyhood of not having too many nodes in pq
     */
    // Sort by value-to-weight ratio (required for upper bound to work correctly)
    sort(pallets.begin(), pallets.end(), sortPallets);

    priority_queue<Node> pq;
    vector<bool> bestSelection(n, false);
    int maxProfit = INT_MIN;

    // Initialize root node
    Node root;
    root.level = -1;
    root.cost = 0;
    root.weight = 0;
    root.selectedPallets = vector<bool>(n, false);
    root.upperBound = upperBound(root, pallets, capacity);
    pq.push(root);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.upperBound <= maxProfit) continue;

        // Try including next pallet
        if (current.level + 1 < n) {
            Node include = current;
            include.level++;
            include.selectedPallets[include.level] = true;
            include.cost += pallets[include.level].getPalletValue();
            include.weight += pallets[include.level].getPalletWeight();

            if (include.weight <= capacity && include.cost > maxProfit) {
                maxProfit = include.cost;
                bestSelection = include.selectedPallets;
            }

            include.upperBound = upperBound(include, pallets, capacity);
            if (include.upperBound > maxProfit) pq.push(include);
        }

        // Try excluding next pallet
        if (current.level + 1 < n) {
            Node exclude = current;
            exclude.level++;
            exclude.upperBound = upperBound(exclude, pallets, capacity);
            if (exclude.upperBound > maxProfit) pq.push(exclude);
        }
    }

    // Build the result using best selection
    vector<Pallet> result;
    for (int i = 0; i < n; ++i) {
        if (bestSelection[i]) {
            result.push_back(pallets[i]);
            truck.addPallet(pallets[i]);
        }
    }

    truck.setCurrProfit(maxProfit);
    truck.setTotalPalletsNum(result.size());

    return result;
}