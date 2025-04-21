#include "batchLogic.h"

void batchMode(const int datasetNum, const int algMode) {
    string inFileTruck;
    string inFilePallet;
    string outFile = "src/output.txt";

    if (datasetNum < 10) {
        inFileTruck = "../docs/datasets/TruckAndPallets_0" + to_string(datasetNum) + ".csv";
        inFilePallet = "../docs/datasets/Pallets_0" + to_string(datasetNum) + ".csv";
    } else {
        inFileTruck = "docs/datasets/TruckAndPallets_10.csv";
        inFilePallet = "docs/datasets/Pallets_10.csv";
    }

    ifstream inTruck(inFileTruck);
    ifstream inPallet(inFilePallet);
    ofstream out(outFile);

    if (!inTruck.is_open() || !inPallet.is_open()) {
        cerr << RED "Error opening input files." RESET << endl;
        return;
    }

    // convert csv files data onto structures
    initializeData(inTruck, inPallet);
    return;
}
