// https://youtu.be/cJ21moQpofY?si=HXmmXDoOJQWwZkn0

#include "dynamicProgAlg.h"
vector<Pallet> DynamicProgramingAlgorithm(Truck& truck, vector<Pallet>& pallets) {
    // Extract truck constraints
    const int maxWeight = truck.getMaxWeight();    // Maximum weight the truck can carry
    const int numPallets = truck.getTotalPalletsNum();  // Total number of pallets available

    // Extract weight and value information from pallets
    vector<int> weights, values, ids;
    for (Pallet p : pallets) {
        weights.push_back(p.getPalletWeight());
        values.push_back(p.getPalletValue());
        ids.push_back(p.getPalletId());  // Assuming there's a getPalletId() method
    }

    // Create DP table with three criteria:
    // - dp[i][w].first = maximum total value possible
    // - dp[i][w].second.first = minimum number of pallets needed to achieve that value
    // - dp[i][w].second.second = sum of IDs of pallets in the solution (we'll minimize this)
    //   (Using sum of IDs as a proxy for "smallest IDs" - solutions with smaller IDs will have smaller sums)
    vector<vector<pair<int, pair<int, long long>>>> dp(numPallets + 1,
                                                     vector<pair<int, pair<int, long long>>>(maxWeight + 1,
                                                     {0, {0, 0}}));

    // Fill the DP table row by row (considering one more pallet each time)
    for (int i = 1; i <= numPallets; i++) {
        // Current pallet under consideration has index (i-1) in the original array
        int currentWeight = weights[i - 1];
        int currentValue = values[i - 1];
        int currentId = ids[i - 1];

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
                int palletsWithoutCurrent = dp[i - 1][w].second.first;
                long long idSumWithoutCurrent = dp[i - 1][w].second.second;

                // Option 2: Include the current pallet
                int valueWithCurrent = dp[i - 1][w - currentWeight].first + currentValue;
                int palletsWithCurrent = dp[i - 1][w - currentWeight].second.first + 1; // Add 1 for this pallet
                long long idSumWithCurrent = dp[i - 1][w - currentWeight].second.second + currentId; // Add this ID to sum

                // Decision logic with optimizations (with nested priority):
                if (valueWithCurrent > valueWithoutCurrent) {
                    // Priority 1: Higher value - choose this option
                    dp[i][w] = {valueWithCurrent, {palletsWithCurrent, idSumWithCurrent}};
                }
                else if (valueWithCurrent == valueWithoutCurrent) {
                    // Equal value - check pallet count (Priority 2)
                    if (palletsWithCurrent < palletsWithoutCurrent) {
                        // Fewer pallets is better
                        dp[i][w] = {valueWithCurrent, {palletsWithCurrent, idSumWithCurrent}};
                    }
                    else if (palletsWithCurrent == palletsWithoutCurrent) {
                        // Equal pallet count - check ID sum (Priority 3)
                        if (idSumWithCurrent < idSumWithoutCurrent) {
                            // Smaller ID sum is better
                            dp[i][w] = {valueWithCurrent, {palletsWithCurrent, idSumWithCurrent}};
                        }
                        else {
                            // Keep the solution with smaller ID sum
                            dp[i][w] = {valueWithoutCurrent, {palletsWithoutCurrent, idSumWithoutCurrent}};
                        }
                    }
                    else {
                        // Keep solution with fewer pallets
                        dp[i][w] = {valueWithoutCurrent, {palletsWithoutCurrent, idSumWithoutCurrent}};
                    }
                }
                else {
                    // Excluding the pallet gives better value - keep previous solution
                    dp[i][w] = {valueWithoutCurrent, {palletsWithoutCurrent, idSumWithoutCurrent}};
                }
            }
        }
    }

    // Backtrack through the DP table to reconstruct the optimal solution
    vector<Pallet> result;
    int remainingWeight = maxWeight;

    // Start from the bottom-right of the DP table (optimal solution for all pallets and full weight)
    for (int i = numPallets; i > 0 && remainingWeight > 0; i--) {
        // Get current pallet's properties
        int currentWeight = weights[i - 1];
        int currentValue = values[i - 1];
        int currentId = ids[i - 1];

        // Check if this pallet is part of the optimal solution by verifying:
        // 1. The pallet fits within remaining weight
        // 2. The solution with this pallet matches our optimal criteria
        if (currentWeight <= remainingWeight &&
            dp[i][remainingWeight].first == dp[i - 1][remainingWeight - currentWeight].first + currentValue &&
            dp[i][remainingWeight].second.first == dp[i - 1][remainingWeight - currentWeight].second.first + 1 &&
            dp[i][remainingWeight].second.second == dp[i - 1][remainingWeight - currentWeight].second.second + currentId) {

            // This pallet is part of our solution
            result.push_back(pallets[i - 1]);

            // Update remaining weight capacity
            remainingWeight -= currentWeight;
        }
        // If conditions aren't met, this pallet isn't in our solution, move to next one
    }

    // Our backtracking gave pallets in reverse order, so flip it
    reverse(result.begin(), result.end());

    return result;  // Return the optimal set of pallets
}