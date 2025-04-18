#ifndef TRUCK_H
#define TRUCK_H

#include <vector>
#include "pallet.h"

class Truck {
    private:
        int maxWeight = -1; // store truck weight capacity
        int currProfit = -1;// store truck current profit
        vector<Pallet> currPallets;// store current pallets in truck
    public:
        int getMaxWeight() const;
        int getCurrProfit() const;
        void setMaxWeight(int maxWeight);
        void setCurrProfit(int currProfit);
        vector<Pallet> getCurrPallets() const;
        void addPallet (const Pallet &pallet);
        void removePallet (Pallet& pallet);
};

inline int Truck::getMaxWeight() const {
    return maxWeight;
}

inline int Truck::getCurrProfit() const {
    return currProfit;
}

inline void Truck::setMaxWeight(const int maxWeight) {
    Truck::maxWeight = maxWeight;
}
inline void Truck::setCurrProfit(const int currProfit) {
    Truck::currProfit = currProfit;
}

inline vector<Pallet> Truck::getCurrPallets() const {
    return currPallets;
}

inline void Truck::addPallet (const Pallet& pallet) {
    currPallets.push_back(pallet);
}

inline void Truck::removePallet (Pallet& pallet) {
    for (auto it = currPallets.begin(); it != currPallets.end(); it++) {
        if (it->getPalletId()==pallet.getPalletId()) {
            currPallets.erase(it);
        }

    }
}
#endif