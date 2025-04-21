#ifndef ILPALG_H
#define ILPALG_H

#include <vector>
#include <iostream>
#include "truck.h"
#include "pallet.h"

using namespace std;
vector<vector<int>> ILPAlgorithm (Truck& truck, vector<Pallet>& pallet);

#endif