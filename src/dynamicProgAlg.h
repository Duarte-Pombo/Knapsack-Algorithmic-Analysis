#ifndef DYNAMICPROGALG_H
#define DYNAMICPROGALG_H
#include <vector>
#include <algorithm>
#include <iostream>
#include "truck.h"
#include "pallet.h"

using namespace std;
<<<<<<< HEAD

=======
>>>>>>> 7765a55ca1c48a168398ff8f1ff306e19107b4f3
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