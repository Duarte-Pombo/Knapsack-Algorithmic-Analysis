#include "parseDataSet.h"

void initializeData(ifstream &truckData, ifstream &palletData, Truck &truck, vector<Pallet> &palletList) {
    truck = initializeTruck(truckData);
    palletList = initializePallet(palletData);
}

Truck initializeTruck(ifstream &truckData) {
    Truck truck;
    string line;

    // Skip header
    getline(truckData, line);

    // Read the next line with the truck data
    if (getline(truckData, line)) {
        stringstream ss(line);
        string value;

        // Capacity
        getline(ss, value, ',');
        const int capacity = stoi(value);
        truck.setMaxWeight(capacity);

        // Pallet count (can be ignored if you’re using the pallet file separately)
        getline(ss, value, ',');
        const int numPallets = stoi(value);
        truck.setTotalPalletsNum(numPallets);

    }

    // Set initial profit to 0
    truck.setCurrProfit(0);

    return truck;
}

// Parse Pallet CSV file
vector<Pallet> initializePallet(ifstream &palletData) {
    vector<Pallet> palletList;
    string line;
    // Skip header
    getline(palletData, line);

    while (getline(palletData, line)) {
        stringstream ss(line);
        string value;
        int id, weight, profit;

        // ID
        getline(ss, value, ',');
        id = stoi(value);

        // Weight
        getline(ss, value, ',');
        weight = stoi(value);

        // Profit
        getline(ss, value, ',');
        profit = stoi(value);

        // Create Pallet with inTruck = false
        Pallet p(false, id, weight, profit);
        palletList.push_back(p);

    }

    return palletList;
}