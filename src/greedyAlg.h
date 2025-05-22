#ifndef GREEDYALG_H
#define GREEDYALG_H
#include <vector>
#include <algorithm>
#include "truck.h"
#include "pallet.h"

using namespace std;
<<<<<<< HEAD

=======
>>>>>>> 7765a55ca1c48a168398ff8f1ff306e19107b4f3
/**
 * @brief Sorts pallets by value-to-weight ratio in descending order.
 * @param pa First pallet.
 * @param pb Second pallet.
 * @return True if pa has a higher ratio than pb.
<<<<<<< HEAD
 * @complexity O(1).
 */
bool sortPallets(const Pallet &pa, const Pallet &pb);

=======
 */
bool sortPallets (const Pallet &pa, const Pallet &pb);
>>>>>>> 7765a55ca1c48a168398ff8f1ff306e19107b4f3
/**
 * @brief Solves the pallet selection problem using a greedy algorithm.
 * @param truck Truck object.
 * @param pallet List of pallets.
 * @return Vector of selected pallets.
 * @complexity O(n log n), where n is the number of pallets (due to sorting).
 */
<<<<<<< HEAD
vector<Pallet> GreedyAlgorithm(Truck& truck, vector<Pallet>& pallet);
=======
vector<Pallet> GreedyAlgorithm (Truck& truck, vector<Pallet>& pallet);
>>>>>>> 7765a55ca1c48a168398ff8f1ff306e19107b4f3

#endif
