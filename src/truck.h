#ifndef TRUCK_H
#define TRUCK_H

#include <vector>
#include "pallet.h"

/**
 * @class Truck
 * @brief Represents a truck with a weight capacity and a collection of pallets.
 */
class Truck {
    private:
        int maxWeight = -1; // store truck weight capacity
        int currProfit = -1;// store truck current profit
        int totalPalletsNum = -1; // store total number of pallets available for packing
        vector<Pallet> currPallets;// store current pallets in truck
    public:
        /**
         * @brief Gets the maximum weight capacity of the truck.
         * @return Maximum weight capacity.
         * @complexity O(1) time, O(1) space.
         */
        int getMaxWeight() const;

        /**
         * @brief Gets the current profit of the truck.
         * @return Current profit.
         * @complexity O(1) time, O(1) space.
         */
        int getCurrProfit() const;

        /**
         * @brief Gets the total number of pallets available for packing.
         * @return Total number of pallets.
         * @complexity O(1) time, O(1) space.
         */
        int getTotalPalletsNum() const;

        /**
         * @brief Sets the maximum weight capacity of the truck.
         * @param maxWeight Maximum weight capacity.
         * @complexity O(1) time, O(1) space.
         */
        void setMaxWeight(int maxWeight);

        /**
         * @brief Sets the current profit of the truck.
         * @param currProfit Current profit.
         * @complexity O(1) time, O(1) space.
         */
        void setCurrProfit(int currProfit);

        /**
         * @brief Sets the total number of pallets available for packing.
         * @param totalPalletsNum Total number of pallets.
         * @complexity O(1) time, O(1) space.
         */
        void setTotalPalletsNum(int totalPalletsNum);

        /**
         * @brief Gets the current pallets in the truck.
         * @return Vector of pallets.
         * @complexity O(1) time, O(n) space, where n is the number of pallets.
         */
        vector<Pallet> getCurrPallets() const;

        /**
         * @brief Adds a pallet to the truck.
         * @param pallet Pallet to add.
         * @complexity O(1) time, O(1) space.
         */
        void addPallet(const Pallet &pallet);

        /**
         * @brief Removes a pallet from the truck.
         * @param pallet Pallet to remove.
         * @complexity O(n) time, O(1) space, where n is the number of pallets.
         */
        void removePallet(Pallet &pallet);
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