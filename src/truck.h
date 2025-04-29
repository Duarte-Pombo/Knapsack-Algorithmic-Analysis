#ifndef TRUCK_H
#define TRUCK_H

#include <vector>
#include "pallet.h"

class Truck {
    private:
        int maxWeight = -1; // store truck weight capacity
        int currProfit = -1;// store truck current profit
        int totalPalletsNum = -1; // store total number of pallets available for packing
        vector<Pallet> currPallets;// store current pallets in truck
    public:
        int getMaxWeight() const;
        int getCurrProfit() const;
        int getTotalPalletsNum() const;
        void setMaxWeight(int maxWeight);
        void setCurrProfit(int currProfit);
        void setTotalPalletsNum(int totalPalletsNum);
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

inline int Truck::getTotalPalletsNum() const {
    return totalPalletsNum;
}

inline void Truck::setMaxWeight(const int maxWeight) {
    Truck::maxWeight = maxWeight;
}
inline void Truck::setCurrProfit(const int currProfit) {
    Truck::currProfit = currProfit;
}

inline void Truck::setTotalPalletsNum(const int totalPalletsNum) {
    Truck:: totalPalletsNum = totalPalletsNum;
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