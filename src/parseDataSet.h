#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "truck.h"
#include "pallet.h"

#ifndef PARSEDATASET_H
#define PARSEDATASET_H

using namespace std;

void initializeData(ifstream &truckData, ifstream &palletData);
Truck initializeTruck(ifstream &truckData); // returns truck info
vector<Pallet> initializePallet(ifstream &palletData); //returns a list with all the pallets

#endif