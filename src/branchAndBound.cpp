#include "branchAndBoundAlternitive.h"

vector<Pallet> BranchAndBound (Truck& truck, vector<Pallet>& pallet) {
    //sort pallets by value-to-weight ratio (desc)
    auto sorted = pallet;
    sort(sorted.begin(), sorted.end(), sortPallets);

    priority_queue<Node> pqueue;

    //init a node
    Node u;
    u.nodeLevel = -1;
    u.nodeProfit = 0;
    u.nodeWeight = 0;
    u.palletsInNode = vector<bool> (truck.getTotalPalletsNum(), false);
    u.bound =  bound(u, pallet, truck.getMaxWeight());
    pqueue.push(u);

    Node v;

    int maxProfit = 0;
    vector<bool> bestSelection (truck.getTotalPalletsNum(), false);

    while (!pqueue.empty()) {
        // analise the top of the pqueue node
        u = pqueue.top();
        pqueue.pop();

        if (u.bound <= maxProfit) { continue; } // prune branch

        // move to the next pallet
        v.nodeLevel = u.nodeLevel + 1;
        if (v.nodeLevel >= truck.getTotalPalletsNum()) { continue;}

        // COMPUTE THE AFTERMATH OF ADDING OR NOT THE NEXT PALLET AND IF ITS WORTH ADDING TO vector<bool> bestSelection;

        // SCENARIO 1: add the pallet at v.level
        v.nodeProfit = u.nodeProfit + pallet [v.nodeLevel].getPalletValue();
        v.nodeWeight = u.nodeWeight + pallet[v.nodeLevel].getPalletWeight();
        v.palletsInNode = u.palletsInNode;
        v.palletsInNode[v.nodeLevel] = true; // update previous pallets included in node

        if (v.nodeWeight <= truck.getMaxWeight() && v.nodeProfit > maxProfit) {
            maxProfit = v.nodeProfit;
            bestSelection = v.palletsInNode;
        }

        v.bound = bound(v, pallet, truck.getMaxWeight());
        if (v.bound > maxProfit) {
            pqueue.push(v);
        }

        // SCENARIO 2: dont add the pallet
        v.nodeProfit = u.nodeProfit;
        v.nodeWeight = u.nodeWeight;
        v.palletsInNode = u.palletsInNode;
        v.palletsInNode[v.nodeLevel] = false;

        v.bound = bound(v, pallet, truck.getMaxWeight());

        if (v.bound > maxProfit) {
            pqueue.push(v);
        }
    }

    // reconstruct the res vector
    vector<Pallet> res;
    for (int i = 0; i < truck.getTotalPalletsNum(); i++) {
        if (bestSelection[i]) {
            res.push_back(pallet[i]);
        }
    }

    return res;
}

// calculate the upper bound (max profit) of a node
double bound(const Node& node, const vector<Pallet>& pallets, int capacity) {
    if (node.nodeWeight >= capacity) { return 0;} // no more profit can fit in this node

    double profitBound = node.nodeProfit;
    int level = node.nodeLevel + 1;
    int totalWeight = node.nodeWeight;

    // continue adding pallets (greedy)
    while (level < static_cast<int>(pallets.size()) && totalWeight + pallets[level].getPalletWeight() <= capacity) {
        totalWeight += pallets[level].getPalletWeight();
        profitBound += pallets[level].getPalletValue();
        level++;
    }

    // if there is still space, take fraction of next item
    if (level < static_cast<int>(pallets.size())) {
        int remain = capacity - totalWeight;
        profitBound += static_cast<double>(pallets[level].getPalletValue()) / pallets[level].getPalletWeight() * remain;
    }

    return profitBound;
}
