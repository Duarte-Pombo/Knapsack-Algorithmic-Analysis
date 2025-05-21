#include "truck.h"
#include "pallet.h"
#include <iostream>
#include <fstream>
#include "parseDataSet.h"
#include "bruteForceAlg.h"
#include "dynamicProgAlg.h"
#include "greedyAlg.h"
#include "ILPAlg.h"

#ifndef BATCHLOGIC_H
#define BATCHLOGIC_H

#define BOLD "\033[1m"
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"

using namespace std;

/**
 * @brief Runs the program in batch mode with the specified dataset and algorithm.
 * @param datasetNum Dataset number to load.
 * @param algMode Algorithm number to execute.
 * @complexity O(n) for dataset parsing, plus the complexity of the selected algorithm.
 */
void batchMode(const int datasetNum, const int algMode);

#endif //BATCHLOGIC_H
