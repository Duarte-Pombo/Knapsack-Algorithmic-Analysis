#include "greedyAlg.h"

#include <algorithm>
#include <numeric>

bool sortPallets (const Pallet &pa, const Pallet &pb) {
    const double qA = pa.getPalletValue() / pa.getPalletWeight();
    const double qB = pb.getPalletValue() / pb.getPalletWeight();
    return qA > qB; //higher ratio comes first
}

vector<Pallet> GreedyAlgorithm(Truck &truck, vector<Pallet> &pallet) {
    vector<Pallet> sortedPallets = pallet;

    const int maxWeight = truck.getMaxWeight();
    vector<Pallet> selectedPallets;
    int currWeight = 0;

    //sort pallets by value-to-weight ratio (desc)
    sort(sortedPallets.begin(), sortedPallets.end(), sortPallets);

    //greedy select the best ratio pallets
    for (const Pallet &p : sortedPallets) {
        if (currWeight + p.getPalletWeight() <= maxWeight) {
            selectedPallets.push_back(p);
            currWeight += p.getPalletWeight();
        }
    }

    return selectedPallets;
}


/*
 *Greedy is a heuristic — fast but not always right
        it's not guaranteed to find the optimal solution for the 0/1 knapsack problem — it can be fooled by better ratios that waste space.
 */