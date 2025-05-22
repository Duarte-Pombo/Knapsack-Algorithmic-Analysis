// https://youtu.be/cJ21moQpofY?si=HXmmXDoOJQWwZkn0

#include "dynamicProgAlg.h"
vector<Pallet> DynamicProgramingAlgorithm(Truck& truck, vector<Pallet>& pallets) {

    const int W = truck.getMaxWeight();
    const int n = truck.getTotalPalletsNum();

    vector<int> weights, values, ids;
    for (Pallet p : pallets) {
        weights.push_back(p.getPalletWeight());
        values.push_back(p.getPalletValue());
        ids.push_back(p.getPalletId());
    }

    // init dp table
    vector<vector<pair<int, pair<int, int>>>>
        dp(n + 1,vector<pair<int, pair<int, int>>>(W + 1,{0, {0, 0}}));

    // populate dp table
    for (int i = 1; i <= n; i++) {

        // current pallet info
        int currw = weights[i - 1];
        int currv = values[i - 1];
        int currId = ids[i - 1];

        // fill row
        for (int w = 0; w <= W; w++) {
            // pallet too heavy
            if (currw > w)
                dp[i][w] = dp[i - 1][w]; //dont include pallet in dp cell
            else {
                //calculate cell info with and without curr pallet
                int valueWithoutCurrent = dp[i - 1][w].first;
                int palletsWithoutCurrent = dp[i - 1][w].second.first;
                int idSumWithoutCurrent = dp[i - 1][w].second.second;
                int valueWithCurrent = dp[i - 1][w - currw].first + currv;
                int palletsWithCurrent = dp[i - 1][w - currw].second.first + 1; // add 1 to total pallets
                int idSumWithCurrent = dp[i - 1][w - currw].second.second + currId; // sum id

                // if higher value
                if (valueWithCurrent > valueWithoutCurrent)
                    dp[i][w] = {valueWithCurrent, {palletsWithCurrent, idSumWithCurrent}};
                // if equal value
                else if (valueWithCurrent == valueWithoutCurrent) {
                    //take sol with fewer pallets
                    if (palletsWithCurrent < palletsWithoutCurrent) 
                        dp[i][w] = {valueWithCurrent, {palletsWithCurrent, idSumWithCurrent}};
                    //if same number of pallets
                    else if (palletsWithCurrent == palletsWithoutCurrent) {
                        // take the one with smaller ids (smaller id sum)
                        if (idSumWithCurrent < idSumWithoutCurrent)
                            dp[i][w] = {valueWithCurrent, {palletsWithCurrent, idSumWithCurrent}};
                        else
                            dp[i][w] = {valueWithoutCurrent, {palletsWithoutCurrent, idSumWithoutCurrent}};
                    }
                    else
                        dp[i][w] = {valueWithoutCurrent, {palletsWithoutCurrent, idSumWithoutCurrent}};
                }
                // if lower value take other previous sol
                else 
                    dp[i][w] = {valueWithoutCurrent, {palletsWithoutCurrent, idSumWithoutCurrent}};
            }
        }
    }

    // backtrack dp table
    vector<Pallet> res;
    int remainingW = W;
    
    for (int i = n; i > 0 && remainingW > 0; i--) {
        // current pallet info
        int currw = weights[i - 1];
        int currv = values[i - 1];
        int currId = ids[i - 1];

        // check if pallet is part of solution
        if (currw <= remainingW &&
            dp[i][remainingW].first == dp[i - 1][remainingW - currw].first + currv &&
            dp[i][remainingW].second.first == dp[i - 1][remainingW - currw].second.first + 1 &&
            dp[i][remainingW].second.second == dp[i - 1][remainingW - currw].second.second + currId) {
            res.push_back(pallets[i - 1]);

            remainingW -= currw;
        }
    }

    reverse(res.begin(), res.end());
    return res;
}

