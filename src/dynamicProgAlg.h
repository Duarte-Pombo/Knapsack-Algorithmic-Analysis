#ifndef DYNAMICPROGALG_H
#define DYNAMICPROGALG_H
#include <vector>
#include <algorithm>
#include <iostream>
#include "truck.h"
#include "pallet.h"

using namespace std;

/**
 * @brief Solves the pallet selection problem using dynamic programming.
 * @param truck Truck object.
 * @param pallet List of pallets.
 * @return Vector of selected pallets.
 * @complexity O(n * W), where n is the number of pallets and W is the truck's weight capacity.
 * @space O(n * W), due to the DP table.
 */
vector<Pallet> DynamicProgramingAlgorithm (Truck& truck, vector<Pallet>& pallet);

#endif