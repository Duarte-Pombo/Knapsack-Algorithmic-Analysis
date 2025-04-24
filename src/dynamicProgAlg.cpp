// https://youtu.be/cJ21moQpofY?si=HXmmXDoOJQWwZkn0

#include "dynamicProgAlg.h"

vector<Pallet> DynamicProgramingAlgorithm (Truck& truck, vector<Pallet>& pallet) {
    const int maxWeight = truck.getMaxWeight();
    const int numPallets = truck.getTotalPalletsNum();

    vector<int> weights , values;
    for (Pallet p : pallet) {
        weights.push_back(p.getPalletWeight());
        values.push_back(p.getPalletValue());
    }

    // create a dp table
    // dp[i][w] maximum value to carry using the i first pallets and total weight capacity w
    vector<vector<int>> dp;
    for (int i = 0; i <= numPallets; i++) {
        dp.push_back(vector(maxWeight + 1, 0));
    }

    // populate dp table
    for (int i = 1; i <= numPallets; i++) {
        for (int w = 0; w <= maxWeight; w++) {
            if (weights[i - 1] > w) {
                dp[i][w] = dp[i - 1][w];
            }
            else {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
        }
    }

    // fetch optimal solution
    vector<Pallet> res;
    int maxW = maxWeight;
    for (int i = numPallets; i > 0 && maxW > 0; i--) {
        if (dp[i][maxW] != dp[i - 1][maxW]) {
            res.push_back(pallet[i - 1]);
            maxW -= weights[i - 1];
        }
    }

    // if needed implement this
    //reverse(res.begin(), res.end(), reverseByID);

    return res;
}
