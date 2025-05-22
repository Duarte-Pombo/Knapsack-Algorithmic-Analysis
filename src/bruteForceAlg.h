#ifndef BRUTEFORCEALG_H
#define BRUTEFORCEALG_H
#include <vector>
#include <iostream>
#include "truck.h"
#include "pallet.h"

using namespace std;

/**
 * @brief Solves the pallet selection problem using brute force.
 * @param truck Truck object.
 * @param pallet List of pallets.
 * @return Vector of selected pallets.
 * @complexity O(2^n) time, O(n) space, where n is the number of pallets.
 */
vector<Pallet> BruteForceAlgorithm(Truck& truck, vector<Pallet>& pallet);

#endif