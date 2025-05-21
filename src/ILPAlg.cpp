// source https://www.youtube.com/watch?v=yV1d-b_NeK8&t=133s&ab_channel=AbdulBari
#include "ILPAlg.h"

/**
 * Calculate the upper bound for a node
 * This estimates the maximum possible value that can be achieved from this node onwards
 */
int upperBound(const Node& node, const vector<Pallet>& pallets, int capacity) {
    // If we've exceeded capacity, return 0 as this branch is infeasible
    if (node.weight > capacity) {
        return 0;
    }

    int bound = node.cost;
    int remainingWeight = capacity - node.weight;
    int i = node.level + 1;

    // Greedily add pallets until capacity is full (if possible)
    while (i < pallets.size() && pallets[i].getPalletWeight() <= remainingWeight) {
        bound += pallets[i].getPalletValue();
        remainingWeight -= pallets[i].getPalletWeight();
        i++;
    }

    // Add fraction of next item if space remains (relaxation of integer constraint)
    if (i < pallets.size() && remainingWeight > 0) {
        bound += (pallets[i].getPalletValue() * remainingWeight) / pallets[i].getPalletWeight();
    }

    return bound;
}

/**
 * Multi-criteria optimization ILP Algorithm using Branch and Bound
 * Prioritizes:
 * 1. Maximum profit
 * 2. Minimum number of pallets
 * 3. Lowest pallet IDs when tied on the above criteria
 */
vector<Pallet> ILPAlgorithm(Truck& truck, vector<Pallet>& pallets) {
    // Get problem parameters
    int n = pallets.size();
    int capacity = truck.getMaxWeight();

    // Preserve original pallets since we'll be sorting them
    vector<Pallet> originalPallets = pallets;

    // Sort pallets by value-to-weight ratio (descending) - required for upper bound calculation
    sort(pallets.begin(), pallets.end(), [](const Pallet& a, const Pallet& b) {
        double ratioA = static_cast<double>(a.getPalletValue()) / a.getPalletWeight();
        double ratioB = static_cast<double>(b.getPalletValue()) / b.getPalletWeight();
        if (ratioA != ratioB) {
            return ratioA > ratioB;
        }
        // Higher weight first if ratios are equal
        if (a.getPalletWeight() != b.getPalletWeight()) {
            return a.getPalletWeight() > b.getPalletWeight();
        }
        // Lower ID first if weights are equal
        return a.getPalletId() < b.getPalletId();
    });

    // Priority queue for branch and bound (max heap based on upper bound)
    priority_queue<Node> pq;

    // Track best solution found so far
    vector<int> bestSelection(n, 0);
    int maxProfit = 0;  // Initialize to 0 (no profit)
    int minPalletCount = numeric_limits<int>::max();
    long long minIdSum = numeric_limits<long long>::max();

    // Initialize root node
    Node root;
    root.level = -1;  // No items considered yet
    root.cost = 0;    // No profit yet
    root.weight = 0;  // No weight yet
    root.palletCount = 0;  // No pallets selected yet
    root.idSum = 0;   // No IDs to sum yet
    root.selectedPallets = vector<int>(n, 0);  // Nothing selected yet
    root.upperBound = upperBound(root, pallets, capacity);  // Compute initial upper bound
    pq.push(root);

    // Branch and bound exploration
    while (!pq.empty()) {
        // Get the most promising node
        Node current = pq.top();
        pq.pop();

        // If upper bound is worse than our best solution, prune this branch
        if (current.upperBound < maxProfit) {
            continue;
        }

        // If we've considered all items, check if this is a better solution
        if (current.level == n - 1) {
            if (current.cost > maxProfit ||
                (current.cost == maxProfit && current.palletCount < minPalletCount) ||
                (current.cost == maxProfit && current.palletCount == minPalletCount && current.idSum < minIdSum)) {

                maxProfit = current.cost;
                minPalletCount = current.palletCount;
                minIdSum = current.idSum;
                bestSelection = current.selectedPallets;
            }
            continue;
        }

        // Generate child nodes by considering next level
        int nextLevel = current.level + 1;

        // Try INCLUDING the next item
        if (nextLevel < n) {
            Node includeNode = current;
            includeNode.level = nextLevel;

            // Update node with new item included
            includeNode.weight += pallets[nextLevel].getPalletWeight();
            includeNode.cost += pallets[nextLevel].getPalletValue();
            includeNode.palletCount++;
            includeNode.idSum += pallets[nextLevel].getPalletId();
            includeNode.selectedPallets[nextLevel] = 1;

            // Only consider if weight constraint is satisfied
            if (includeNode.weight <= capacity) {
                // Update best solution if this is better
                if (includeNode.cost > maxProfit ||
                    (includeNode.cost == maxProfit && includeNode.palletCount < minPalletCount) ||
                    (includeNode.cost == maxProfit && includeNode.palletCount == minPalletCount && includeNode.idSum < minIdSum)) {

                    maxProfit = includeNode.cost;
                    minPalletCount = includeNode.palletCount;
                    minIdSum = includeNode.idSum;
                    bestSelection = includeNode.selectedPallets;
                }

                // Calculate upper bound for this node
                includeNode.upperBound = upperBound(includeNode, pallets, capacity);

                // Only add to queue if it could potentially beat the current best solution
                if (includeNode.upperBound > maxProfit) {
                    pq.push(includeNode);
                }
            }
        }

        // Try EXCLUDING the next item
        if (nextLevel < n) {
            Node excludeNode = current;
            excludeNode.level = nextLevel;
            excludeNode.selectedPallets[nextLevel] = 0;

            // Calculate upper bound for this node
            excludeNode.upperBound = upperBound(excludeNode, pallets, capacity);

            // Only add to queue if it could potentially beat the current best solution
            if (excludeNode.upperBound > maxProfit) {
                pq.push(excludeNode);
            }
        }
    }

    // Build the final result using the best selection found
    vector<Pallet> result;
    for (int i = 0; i < n; i++) {
        if (bestSelection[i] == 1) {
            result.push_back(pallets[i]);
        }
    }

    // Return the original paletIDs
    for (int i = 0; i < result.size(); i++) {
        // Find the original pallet that matches this one
        for (int j = 0; j < originalPallets.size(); j++) {
            if (result[i].getPalletId() == originalPallets[j].getPalletId()) {
                truck.addPallet(originalPallets[j]);
                break;
            }
        }
    }

    // Update truck state
    truck.setCurrProfit(maxProfit);
    truck.setTotalPalletsNum(result.size());

    return result;
}