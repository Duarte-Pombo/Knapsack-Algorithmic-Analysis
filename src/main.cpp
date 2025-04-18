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
      string inputFile = argv[1];
      string outputFile = argv[2];
      batchMode(inputFile, outputFile);
      break;
    }
    default:{ // Error handling
      cerr << BOLD RED "ERROR: Invalid Command Line Arguments" RESET << endl;
      cerr << BOLD RED "Usage:" << RESET YELLOW << "(Interactive Mode)" << RESET BOLD RED << " ./Project01" RESET << endl;
      cerr << BOLD RED "Usage:" << RESET YELLOW << "(Batch Mode)" << RESET BOLD RED << " ./Project01 input.txt output.txt" RESET << endl;
      return EXIT_FAILURE;
      break;
    }
  }
  return 0;
}