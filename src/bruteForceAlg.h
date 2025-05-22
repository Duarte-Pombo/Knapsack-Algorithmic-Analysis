#ifndef BRUTEFORCEALG_H
#define BRUTEFORCEALG_H
#include <vector>
#include <iostream>
#include "truck.h"
#include "pallet.h"

using namespace std;
<<<<<<< HEAD

=======
>>>>>>> 7765a55ca1c48a168398ff8f1ff306e19107b4f3
/**
 * @brief Solves the pallet selection problem using brute force.
 * @param truck Truck object.
 * @param pallet List of pallets.
 * @return Vector of selected pallets.
 * @complexity O(2^n), where n is the number of pallets.
 * @space O(n), due to recursion stack.
 */
vector<Pallet> BruteForceAlgorithm (Truck& truck, vector<Pallet>& pallet);

#endif