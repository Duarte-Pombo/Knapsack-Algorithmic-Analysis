#include "truck.h"
#include "pallet.h"
#include <iostream>
#include <fstream>
#include "parseDataSet.h"
#include "bruteForceAlg.h"
#include "dynamicProgAlg.h"
#include "greedyAlg.h"
#include "branchAndBound.h"

#ifndef BATCHLOGIC_H
#define BATCHLOGIC_H

#define BOLD "\033[1m"
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"

using namespace std;
void batchMode(const int datasetNum, const int algMode);

#endif //BATCHLOGIC_H
