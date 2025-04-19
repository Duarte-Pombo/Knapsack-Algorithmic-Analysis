#include <iostream>
#include <fstream>
#include "batchLogic.h"
using namespace std;

void batchMode(const int datasetNum, const int algMode) {
    string inFileTruck;
    string inFilePallet;

    if (datasetNum < 10) {
        inFileTruck = "docs/datasets/TruckAndPallets_0" + to_string(datasetNum) + ".csv";
        inFilePallet = "docs/datasets/Pallets_0" + to_string(datasetNum) + ".csv";
    } else {
        inFileTruck = "docs/datasets/TruckAndPallets_10.csv";
        inFilePallet = "docs/datasets/Pallets_10.csv";
    }

    cout << inFileTruck << endl;
    cout << inFilePallet << endl;

    return;
}
