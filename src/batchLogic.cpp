#include "batchLogic.h"

void batchMode(const int datasetNum, const int algMode) {
    string inFileTruck;
    string inFilePallet;
    string outFile = "../src/output.txt";

    if (datasetNum < 10) {
        inFileTruck = "../docs/datasets/TruckAndPallets_0" + to_string(datasetNum) + ".csv";
        inFilePallet = "../docs/datasets/Pallets_0" + to_string(datasetNum) + ".csv";
    } else {
        inFileTruck = "../docs/datasets/TruckAndPallets_10.csv";
        inFilePallet = "../docs/datasets/Pallets_10.csv";
    }

    ifstream inTruck(inFileTruck);
    ifstream inPallet(inFilePallet);
    ofstream out(outFile);

    Truck truck;
    vector<Pallet> pallets;

    if (!inTruck.is_open() || !inPallet.is_open()) {
        cerr << RED "Error opening input files." RESET << endl;
        return;
    }

    // convert csv files data onto structures
    initializeData(inTruck, inPallet, truck, pallets);

    // DEBUG print
    // cout << "Truck: Capacity: " << truck.getMaxWeight() << endl;
    // cout << "Truck: TotalPalletNum: " << truck.getTotalPalletsNum() << endl;
    // for (int i = 0; i < truck.getTotalPalletsNum(); i++) {
    //     cout << "Pallet[" << pallets[i].getPalletId() << "]: Weight :"<< pallets[i].getPalletWeight() << "  Value : "<< pallets[i].getPalletValue() << endl;
    // }

    vector<vector<int>> optimalSolutionsList;

    switch (algMode) {
        case 1:
            optimalSolutionsList = BruteForceAlgorithm (truck, pallets);
            break;
        // case 2:
        //     optimalSolutionsList = DynamicProgramingAlgorithm (truck, pallets);
        //     break;
        // case 3:
        //     optimalSolutionsList = GreedyAlgorithm (truck, pallets);
        //     break;
        // case 4:
        //     optimalSolutionsList = ILPAlgorithm (truck, pallets);
        //     break;
        default:
            cerr << RED "Not a valid algorithm number input" RESET << endl;
    }

    // write the elements in optimal solution onto the output file
    for (const auto &optimalSolution : optimalSolutionsList) {
        for (size_t i = 0; i < optimalSolution.size(); ++i) {
            out << optimalSolution[i];
            if (i != optimalSolution.size() - 1)
                out << ", ";
        }
        out << '\n';
    }

}
