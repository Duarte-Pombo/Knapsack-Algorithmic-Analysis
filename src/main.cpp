#include <iostream>
#include "menuLogic.h"
#include "batchLogic.h"

using namespace std;

int main(int argc, char** argv) {
   switch (argc){
    case 1:{ //Run interactive mode
      interactiveMode();
      break;
    }
    case 3:{ //Run Batch Mode
      int const datasetNum = stoi(argv[1]);
      int const algMode = stoi(argv[2]);
      batchMode(datasetNum, algMode);
      break;
    }
     default: { // Error handling
      cerr << BOLD RED "ERROR: Invalid Command Line Arguments\n" RESET;
      cerr << BOLD RED "Usage:\n" RESET;
      cerr << RESET YELLOW "  (Interactive Mode) " RESET BOLD RED "./Project02\n" RESET;
      cerr << RESET YELLOW "  (Batch Mode)       " RESET BOLD RED "./Project02 (int)DataSetNumber (int)AlgorithmNumber\n" RESET;

      cerr << "\n" << BOLD "  > DataSetNumber (1-10): Selects the dataset pair to load\n" RESET;
      cerr << "    ┌───────┬──────────────────────────────────────┐\n";
      cerr << "    │ Value │ Dataset Files                        │\n";
      cerr << "    ├───────┼──────────────────────────────────────┤\n";
      for (int i = 1; i <= 10; ++i) {
        cerr << "    │   " << i << "   │ TrunkAndPallets" << i << ".csv, Pallets" << i << ".csv   │\n";
      }
      cerr << "    └───────┴──────────────────────────────────────┘\n";

      cerr << "\n" << BOLD "  > AlgorithmNumber (1-4): Selects the algorithm to use\n" RESET;
      cerr << "    ┌───────┬──────────────────────┬\n";
      cerr << "    │ Value │ Algorithm            │\n";
      cerr << "    ├───────┼──────────────────────┼\n";
      cerr << "    │   1   │ Brute Force          │\n";
      cerr << "    │   2   │ Dynamic Programming  │\n";
      cerr << "    │   3   │ Greedy               │\n";
      cerr << "    │   4   │ ILP                  │\n";
      cerr << "    └───────┴──────────────────────┴\n";

      return EXIT_FAILURE;
      break;
     }

  }
  return 0;
}