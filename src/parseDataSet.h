#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "truck.h"
#include "pallet.h"

#ifndef PARSEDATASET_H
#define PARSEDATASET_H

using namespace std;

/**
 * @brief Initializes the truck and pallet data from input files.
 * @param truckData Input file stream for truck data.
 * @param palletData Input file stream for pallet data.
 * @param truck Truck object to initialize.
 * @param palletList Vector to store the list of pallets.
 * @complexity O(n), where n is the number of pallets in the pallet data file.
 */
void initializeData(ifstream &truckData, ifstream &palletData, Truck &truck, vector<Pallet> &palletList);

/**
 * @brief Initializes the truck object from the input file.
 * @param truckData Input file stream for truck data.
 * @return Initialized Truck object.
 * @complexity O(1), as it reads a fixed amount of data.
 */
Truck initializeTruck(ifstream &truckData);

/**
 * @brief Initializes the list of pallets from the input file.
 * @param palletData Input file stream for pallet data.
 * @return Vector of initialized pallets.
 * @complexity O(n), where n is the number of pallets in the pallet data file.
 */
vector<Pallet> initializePallet(ifstream &palletData);

#endif