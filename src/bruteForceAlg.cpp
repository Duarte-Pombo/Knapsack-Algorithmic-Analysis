#include "bruteForceAlg.h"

using namespace std;

vector<vector<int>> BruteForceAlgorithm(Truck& truck, vector<Pallet>& pallets) {
    const int maxWeight = truck.getMaxWeight();
    const int n = pallets.size();
    int maxValue = 0;
    vector<vector<int>> optSolutions;

    // Iterate over all possible subsets (2^n)
    for (int mask = 0; mask < (1 << n); ++mask) { // (1 << n) = 2^n
        int currWeight = 0;
        int currValue = 0;
        vector<int> currSolution;

        cout << "Evaluating subset mask: " << mask << endl;

        // Check each bit in the mask
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                currWeight += pallets[i].getPalletWeight();
                currValue += pallets[i].getPalletValue();
                currSolution.push_back(pallets[i].getPalletId());

                cout << "  Considering pallet ID " << pallets[i].getPalletId()
                     << " (Weight: " << pallets[i].getPalletWeight()
                     << ", Value: " << pallets[i].getPalletValue() << ")" << endl;
            }
        }

        cout << "  → Subset total weight = " << currWeight
             << ", total value = " << currValue << ", pallets = ";
        for (int id : currSolution) cout << id << " ";
        cout << endl;

        // Check if the subset is valid and optimal
        if (currWeight <= maxWeight) {
            cout << "  Valid subset (within weight limit)" << endl;
            if (currValue > maxValue) {
                maxValue = currValue;
                optSolutions.clear();
                optSolutions.push_back(currSolution);
                cout << "  → New optimal found! Value = " << currValue
                     << ", Weight = " << currWeight << endl;
            } else if (currValue == maxValue && !currSolution.empty()) {
                optSolutions.push_back(currSolution);
                cout << "  → Equal optimal value found (Value = " << currValue << ")" << endl;
            }
        } else {
            cout << "  Subset discarded: overweight (" << currWeight << " > " << maxWeight << ")" << endl;
        }

        cout << "--------------------------------------------------" << endl;
    }

    return optSolutions;
}
