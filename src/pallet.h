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
        void setPalletId(int palletId);
        void setPalletWeight(int palletWeight);
        void setPalletValue(int palletValue);
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