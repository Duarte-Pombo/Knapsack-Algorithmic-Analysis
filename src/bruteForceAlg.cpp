#include "bruteForceAlg.h"

#include <limits.h>

vector<Pallet> BruteForceAlgorithm(Truck& truck, vector<Pallet>& pallets) {
    const int maxWeight = truck.getMaxWeight();
    const int numPallets = truck.getTotalPalletsNum();
    int maxValue = 0;
    vector<vector<Pallet>> optSolutionList;
    vector<Pallet> optSolution;

    // Iterate over all possible subsets (2^n)
    for (int mask = 0; mask < (1 << numPallets); ++mask) {
        int currWeight = 0;
        int currValue = 0;
        vector<Pallet> currSolution;

        for (int i = 0; i < numPallets; ++i) {
            if (mask & (1 << i)) {
                currWeight += pallets[i].getPalletWeight();
                currValue += pallets[i].getPalletValue();
                currSolution.push_back(pallets[i]);
            }
        }

        // Check if the subset is valid and optimal
        if (currWeight <= maxWeight) {
            if (currValue == maxValue) {
                optSolutionList.push_back(currSolution);
            }
            else if (currValue > maxValue) {
                maxValue = currValue;
                optSolutionList.clear(); //invalidate all other solutions previously being considered
                optSolutionList.push_back(currSolution); // store the best current solution
            }
        }
    }

    int smallestSize = INT_MAX;
    for (vector<Pallet> sol : optSolutionList) {
        int currSize = sol.size();
        if (currSize < smallestSize) {
            optSolution = sol;
            smallestSize = currSize;
        }
    }

    return optSolution; //return the optimal solution with the smallest number of elements
}
