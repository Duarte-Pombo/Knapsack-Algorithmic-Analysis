#ifndef MENULOGIC_H
#define MENULOGIC_H

#define BOLD "\033[1m"
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define ITALIC "\033[1;37m"
#define PURPLE "\033[1;35m"

#include <iostream>
#include "truck.h"
#include "pallet.h"
#include <fstream>
#include "parseDataSet.h"
#include "bruteForceAlg.h"
#include "dynamicProgAlg.h"
#include "greedyAlg.h"
#include "ILPAlg.h"

void interactiveMode();
int displayMenu();
void displayProjectInfo();
int displayAlgorithm ();
int displayTruckPalletOption();
void displaySolution(const vector<Pallet>& resList);

#endif //MENULOGIC_H