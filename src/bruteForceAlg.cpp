#include "bruteForceAlg.h"

vector<Pallet> BruteForceAlgorithm(Truck& truck, vector<Pallet>& pallets) {
    const int maxWeight = truck.getMaxWeight();
    const int numPallets = truck.getTotalPalletsNum();
    int maxValue = 0;
    vector<Pallet> optSolutionList;

    // Iterate over all possible subsets (2^n)
    for (int mask = 0; mask < (1 << numPallets); ++mask) {
        int currWeight = 0;
        int currValue = 0;
        vector<Pallet> currSolution;

        // Check all possible combinations
        for (int i = 0; i < numPallets; ++i) {
            if (mask & (1 << i)) {
                currWeight += pallets[i].getPalletWeight();
                currValue += pallets[i].getPalletValue();
                currSolution.push_back(pallets[i]);
            }
        }

        // Check if the subset is valid and optimal
        if (currWeight <= maxWeight) {
            if (currValue > maxValue) {
                maxValue = currValue;
                optSolutionList = currSolution; // store the best current solution
            }
        }
    }

    return optSolutionList;
}
