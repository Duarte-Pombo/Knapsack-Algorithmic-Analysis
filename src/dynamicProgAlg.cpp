// https://youtu.be/cJ21moQpofY?si=HXmmXDoOJQWwZkn0

#include "dynamicProgAlg.h"

vector<Pallet> DynamicProgramingAlgorithm (Truck& truck, vector<Pallet>& pallets) {
    const int maxWeight = truck.getMaxWeight();
    const int numPallets = truck.getTotalPalletsNum();

    vector<int> weights , values;
    for (Pallet p : pallets) {
        weights.push_back(p.getPalletWeight());
        values.push_back(p.getPalletValue());
    }

    // initialize a dp table
    // - dp[i][w].first = maximum total value possible
    // - dp[i][w].second = minimum number of pallets needed to achieve that value
    vector<vector<pair<int, int>>> dp(numPallets + 1, vector<pair<int, int>>(maxWeight + 1, {0, 0}));

    // populate dp table
    for (int i = 1; i <= numPallets; i++) {
        // Current pallet under consideration has index (i-1) in the original array
        int currentWeight = weights[i - 1];
        int currentValue = values[i - 1];

        // For each possible weight capacity from 0 to maxWeight
        for (int w = 0; w <= maxWeight; w++) {
            // CASE 1: Current pallet is too heavy for this weight capacity
            if (currentWeight > w) {
                // Cannot include this pallet, so take solution without it
                dp[i][w] = dp[i - 1][w];
            }
            // CASE 2: We can potentially include or exclude this pallet
            else {
                // Option 1: Exclude the current pallet (use previous solution)
                int valueWithoutCurrent = dp[i - 1][w].first;
                int palletsWithoutCurrent = dp[i - 1][w].second;

                // Option 2: Include the current pallet
                int valueWithCurrent = dp[i - 1][w - currentWeight].first + currentValue;
                int palletsWithCurrent = dp[i - 1][w - currentWeight].second + 1; // Add 1 for this pallet

                // Decision logic with optimizations:
                if (valueWithCurrent > valueWithoutCurrent) {
                    // Including the pallet gives better value - choose this option
                    dp[i][w] = {valueWithCurrent, palletsWithCurrent};
                }
                else if (valueWithCurrent == valueWithoutCurrent) {
                    // Both options give same value - choose the one with fewer pallets
                    if (palletsWithCurrent < palletsWithoutCurrent) {
                        dp[i][w] = {valueWithCurrent, palletsWithCurrent};
                    } else {
                        dp[i][w] = {valueWithoutCurrent, palletsWithoutCurrent};
                    }
                }
                else {
                    // Excluding the pallet gives better value - keep previous solution
                    dp[i][w] = {valueWithoutCurrent, palletsWithoutCurrent};
                }
            }
        }
    }

    // fetch optimal solution FIX: fetch the lowest ammount of pallets solution
    vector<Pallet> res;
    int remainingWeight = maxWeight;
    for (int i = numPallets; i > 0 && remainingWeight > 0; i--) {
        // Get current pallet's properties
        int currentWeight = weights[i - 1];
        int currentValue = values[i - 1];

        // Check if this pallet is part of the optimal solution by verifying:
        // 1. The pallet fits within remaining weight
        // 2. Including this pallet gives the optimal value at this position
        // 3. The pallet count increases by exactly 1 when this pallet is included
        if (currentWeight <= remainingWeight &&
            dp[i][remainingWeight].first == dp[i - 1][remainingWeight - currentWeight].first + currentValue &&
            dp[i][remainingWeight].second == dp[i - 1][remainingWeight - currentWeight].second + 1) {

            // This pallet is part of our solution
            res.push_back(pallets[i - 1]);

            // Update remaining weight capacity
            remainingWeight -= currentWeight;
            }
        // If conditions aren't met, this pallet isn't in our solution, move to next one
    }

    reverse(res.begin(), res.end());

    return res;
}
