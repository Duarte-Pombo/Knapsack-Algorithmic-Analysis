#include "menuLogic.h"


using namespace std;

void interactiveMode(){
  int option = displayMenu();

      if (option == 1) { //display options
        int dataSetOption = displayTruckPalletOption();
          string inFileTruck;
          string inFilePallet;

          if (dataSetOption < 10) {
              inFileTruck = "../docs/datasets/TruckAndPallets_0" + to_string(dataSetOption) + ".csv";
              inFilePallet = "../docs/datasets/Pallets_0" + to_string(dataSetOption) + ".csv";
          } else {
              inFileTruck = "../docs/datasets/TruckAndPallets_10.csv";
              inFilePallet = "../docs/datasets/Pallets_10.csv";
          }

          ifstream inTruck(inFileTruck);
          ifstream inPallet(inFilePallet);

          if (!inTruck.is_open() || !inPallet.is_open()) {
              cerr << RED "Error opening input files." RESET << endl;
              return;
          }
          Truck truck;
          vector<Pallet> pallets;

          initializeData(inTruck, inPallet, truck, pallets);

          vector<Pallet> optimalSolutionList;

          cout << endl;
          int algMode = displayAlgorithm ();

          cout << endl;
          cout << BOLD PURPLE "○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──" RESET << endl;
          cout << PURPLE BOLD "PALLET SELECTION INFO" RESET << endl ;
          cout << YELLOW  "Weight Limit in Truck > " RESET<< truck.getMaxWeight() << endl ;
          cout << YELLOW  "Total Number of Pallets to Select From > "  RESET << truck.getTotalPalletsNum() << endl;
          cout << BOLD PURPLE "○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──" RESET << endl;

          switch (algMode) {
              case 1:
                  optimalSolutionList = BruteForceAlgorithm (truck, pallets);
                  break;
              case 2:
                  optimalSolutionList = DynamicProgramingAlgorithm (truck, pallets);
                  break;
              case 3:
                  optimalSolutionList = GreedyAlgorithm (truck, pallets);
                  break;
              case 4:
                  optimalSolutionList = ILPAlgorithm (truck, pallets);
                  break;
              default:
                  cerr << RED "Not a valid algorithm number input" RESET << endl;
          }
          displaySolution(optimalSolutionList);
      }
      else if (option == 2) {
        displayProjectInfo(); //display projects info
      }
      else {
        cout << BOLD ">> Exited" RESET << endl;
      }
      return;
}


int displayMenu(){
    int option;
    do {
        cout <<"\n" << endl;
        cout << GREEN BOLD "=========== MENU =========== \n"  RESET<< endl;
        cout << "1. Chose Pallet Selection Algorithm \n" << endl;
        cout << "2. View Project Information \n" << endl;
        cout << RED "3. Exit\n"  RESET<< endl;
        cout << GREEN BOLD "============================" RESET << endl;
        cout << YELLOW BOLD "> Enter your option: "  RESET;
        cin >> option;

        if (cin.fail()) {
            cout << RED BOLD ">> Please enter a Valid Number" RESET << endl;
            cin.clear();
            cin.ignore();
            option = -1; // trigger loop
            continue;
        }

        if (option >3 || option < 1) {
            cout << RED BOLD ">> Invalid Option" RESET<< endl;
        }
    } while (option < 1 || option > 3);

    return option;
}

void displayProjectInfo() {
    cout << "\n";
    cout << GREEN BOLD "========================================================" RESET << endl;
    cout << YELLOW BOLD"                 PALLET OPTIMIZATION TOOL               " RESET << endl;
    cout << GREEN BOLD "========================================================" RESET << endl;
    cout << "\n";
    cout <<            "This project tackles the 0/1 Knapsack Problem in a realistic" << endl;
    cout <<            "logistics context. It aims to help select the optimal combination" << endl;
    cout <<            "of pallets to load onto a truck to maximize value without" << endl;
    cout <<            "exceeding the truck’s weight capacity." << endl;
    cout << "\n";
    cout << YELLOW BOLD">> INCLUDED FEATURES:" RESET << endl;
    cout <<            "✔ Exhaustive Search Approach of the most Optimal Solution ;" << endl;
    cout <<            "✔ Integer Linear Programming (ILP) formulation and solution;" << endl;
    cout <<            "✔ Dynamic Programming (DP) approach with backtracking;" << endl;
    cout <<            "✔ Greedy heuristic for fast approximations;" << endl;
    cout <<            "✔ Full comparison of results and performance for each method;" << endl;
    cout << "\n";
    cout << YELLOW BOLD">> PRIMARY ALGORITHMS USED:" RESET << endl;
    cout <<            "◉ Exaustive Search;" << endl;
    cout <<            "◉ Integer Linear Programming (ILP);" << endl;
    cout <<            "◉ Dynamic Programming with 2D memoization table;" << endl;
    cout <<            "◉ Greedy algorithm based on value-to-weight ratio;" << endl;
    cout << "\n";
    cout << YELLOW BOLD">> AUTHORS:" RESET << endl;
    cout <<            "Dinis Cabral Lima" << endl;
    cout <<            "Diogo Alves Martins" << endl;
    cout <<            "Duarte Pombo Martins" << endl;
    cout << "\n";
    cout << GREEN BOLD "========================================================" RESET << endl;
    cout << YELLOW BOLD"           FEUP || DESENHO DE ALGORITMOS 2025           " RESET << endl;
    cout << GREEN BOLD "========================================================" RESET << endl;
    cout << "\n";
}

int displayAlgorithm () {
    int alg;
    do {
        cout << BOLD BLUE ">> Choose Algorithm Approach" RESET << endl;
        cout << "1. Exhaustive Search " << endl;
        cout << "2. Dynamic Programming " << endl;
        cout << "3. Greedy Approach " << endl;
        cout << "4. Integer Linear Programing " << endl;

        cout << YELLOW BOLD "> Enter your Algorithm of Choice: "  RESET;
        cin >> alg;

        if (cin.fail()) {
            cout << RED BOLD ">> Please enter a Valid Number" RESET << endl;
            cin.clear();
            cin.ignore();
            alg = -1; // trigger loop
            continue;
        }
        if (alg > 4 || alg < 1) {
            cout << RED BOLD ">> Invalid Option" RESET<< endl;
        }
    } while (alg < 1 || alg > 4);

    return alg;
}

int displayTruckPalletOption() {
    int option;
    do {
        cout << BOLD BLUE ">> Choose Truck/Pallet Dataset" RESET << endl;
        cout << "(1-10) TrucksAndPallets_X.csv // Pallets_X.csv " << endl;

        cout << YELLOW BOLD "> Enter your Dataset of Choice: "  RESET;
        cin >> option;

        if (cin.fail()) {
            cout << RED BOLD ">> Please enter a Valid Number" RESET << endl;
            cin.clear();
            cin.ignore();
            option = -1; // trigger loop
            continue;
        }
        if (option > 10 || option < 1) {
            cout << RED BOLD ">> Invalid Option" RESET<< endl;
        }
    } while (option < 1 || option > 10);

    return option;
}

void displaySolution(const vector<Pallet>& resList) {
    cout << BOLD BLUE "○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──" RESET << endl;
    cout << BLUE BOLD "PALLET SOLUTION LIST" RESET << endl ;
    int totalWeight = 0;
    int totalProfit = 0;
    // write the elements in optimal solution onto the terminal
    for (const auto &optimalSolution : resList) {
        totalWeight += optimalSolution.getPalletWeight();
        totalProfit += optimalSolution.getPalletValue();
        cout << optimalSolution.getPalletId() << ", " << optimalSolution.getPalletWeight() << ", " << optimalSolution.getPalletValue() << endl;
    }

    cout << YELLOW BOLD"Total weight in truck: " RESET<< totalWeight << endl ;
    cout << YELLOW BOLD "Total profit in truck: "  RESET << totalProfit << endl;
    cout << BOLD BLUE "○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──○──" RESET << endl;
}
