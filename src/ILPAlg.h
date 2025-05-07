#ifndef ILPALG_H
#define ILPALG_H

#include "truck.h"
#include "pallet.h"
#include <queue>
#include <vector>
#include "greedyAlg.h"
#include <climits>
using namespace std;

int getUpperBound(Node node, vector<Pallet>& pallets, int capacity);
vector<Pallet> ILPAlgorithm (Truck& truck, vector<Pallet>& pallet);

#endif