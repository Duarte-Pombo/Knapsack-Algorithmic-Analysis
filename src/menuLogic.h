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

/**
 * @brief Runs the interactive mode for the program.
 * @complexity O(1) time, excluding algorithm execution.
 */
void interactiveMode();

/**
 * @brief Displays the main menu and gets the user's choice.
 * @return User's menu choice.
 * @complexity O(1) time, O(1) space.
 */
int displayMenu();

/**
 * @brief Displays project information.
 * @complexity O(1) time, O(1) space.
 */
void displayProjectInfo();

/**
 * @brief Displays the algorithm selection menu and gets the user's choice.
 * @return User's algorithm choice.
 * @complexity O(1) time, O(1) space.
 */
int displayAlgorithm();

/**
 * @brief Displays the truck and pallet options menu and gets the user's choice.
 * @return User's choice for truck/pallet options.
 * @complexity O(1) time, O(1) space.
 */
int displayTruckPalletOption();

/**
 * @brief Displays the solution (selected pallets) to the user.
 * @param resList Vector of selected pallets.
 * @complexity O(n) time, O(1) space, where n is the number of pallets.
 */
void displaySolution(const vector<Pallet>& resList);
