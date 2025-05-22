#ifndef GREEDYALG_H
#define GREEDYALG_H
#include <vector>
#include <algorithm>
#include "truck.h"
#include "pallet.h"

using namespace std;
/**
 * @brief Sorts pallets by value-to-weight ratio in descending order.
 * @param pa First pallet.
 * @param pb Second pallet.
 * @return True if pa has a higher ratio than pb.
 * @complexity O(1).
 */
bool sortPallets(const Pallet &pa, const Pallet &pb);

/**
 * @brief Solves the pallet selection problem using a greedy algorithm.
 * @param truck Truck object.
 * @param pallet List of pallets.
 * @return Vector of selected pallets.
 * @complexity O(n log n) time (due to sorting), O(1) space.
 */
vector<Pallet> GreedyAlgorithm(Truck& truck, vector<Pallet>& pallet);

#endif
