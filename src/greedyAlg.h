#ifndef GREEDYALG_H
#define GREEDYALG_H
#include <vector>
#include <algorithm>
#include "truck.h"
#include "pallet.h"

using namespace std;
bool sortPallets (const Pallet &pa, const Pallet &pb);
vector<Pallet> GreedyAlgorithm (Truck& truck, vector<Pallet>& pallet);

#endif
