#ifndef PALLET_H
#define PALLET_H

#include <iostream>

using namespace std;

/**
 * @class Pallet
 * @brief Represents a pallet with weight, value, and truck status.
 */
class Pallet {
    private:
        bool inTruck;
        int palletId;
        int palletWeight;
        int palletValue;
    public:
        /**
         * @brief Constructs a Pallet object.
         * @param inTruck Whether the pallet is in the truck.
         * @param palletId ID of the pallet.
         * @param palletWeight Weight of the pallet.
         * @param palletValue Value of the pallet.
         */
        Pallet(const bool inTruck, const int palletId, const int palletWeight, const int palletValue)
            : inTruck(inTruck), palletId(palletId), palletWeight(palletWeight), palletValue(palletValue) {}

        /**
         * @brief Gets the ID of the pallet.
         * @return Pallet ID.
         * @complexity O(1) time, O(1) space.
         */
        int getPalletId() const;

        /**
         * @brief Gets the weight of the pallet.
         * @return Pallet weight.
         * @complexity O(1) time, O(1) space.
         */
        int getPalletWeight() const;

        /**
         * @brief Gets the value of the pallet.
         * @return Pallet value.
         * @complexity O(1) time, O(1) space.
         */
        int getPalletValue() const;

        /**
         * @brief Sets the ID of the pallet.
         * @param palletId Pallet ID.
         * @complexity O(1) time, O(1) space.
         */
        void setPalletId(int palletId);

        /**
         * @brief Sets the weight of the pallet.
         * @param palletWeight Pallet weight.
         * @complexity O(1) time, O(1) space.
         */
        void setPalletWeight(int palletWeight);

        /**
         * @brief Sets the value of the pallet.
         * @param palletValue Pallet value.
         * @complexity O(1) time, O(1) space.
         */
        void setPalletValue(int palletValue);

        /**
         * @brief Sets whether the pallet is in the truck.
         * @param inTruck Truck status.
         * @complexity O(1) time, O(1) space.
         */
        void setPalletInTruck(bool inTruck);
};

inline int Pallet::getPalletId() const {
    return palletId;
}

inline int Pallet::getPalletWeight() const {
    return palletWeight;
}

inline int Pallet::getPalletValue() const {
    return palletValue;
}

inline void Pallet::setPalletId(const int palletId) {
    this->palletId = palletId;
}

inline void Pallet::setPalletWeight(const int palletWeight) {
    this->palletWeight = palletWeight;
}

inline void Pallet::setPalletValue(const int palletValue) {
    this->palletValue = palletValue;
}

inline void Pallet::setPalletInTruck(const bool inTruck) {
    this->inTruck = inTruck;
}
#endif