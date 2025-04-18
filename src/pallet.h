#ifndef PALLET_H
#define PALLET_H

#include <iostream>

using namespace std;

class Pallet {
    private:
        bool inTruck;
        int palletId;
        int palletWeight;
        int palletValue;
    public:
        Pallet(const bool inTruck, const int palletId, const int palletWeight, const int palletValue)
            : inTruck(inTruck), palletId(palletId), palletWeight(palletWeight), palletValue(palletValue) {}
        int getPalletId() const;
        int getPalletWeight() const;
        int getPalletValue() const;
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

inline void Pallet::setPalletInTruck(const bool inTruck) {
    this->inTruck = inTruck;
}
#endif