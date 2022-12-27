#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#include "Greedy.h"
#include "Classifier.h"
#include "Validator.h"
#include "Normalizer.h"

using namespace std;

int main(){
	vector<vector<double>> trainInstances;
    vector<double> trainLabels;

	cout << "Welcome to Kevin Gao's Feature Selection Algorithm" << endl;

	cout << "Type in the name of the file to test: ";
	string fileInput;
    cin >> fileInput;

    cout << endl << "Type the number of the algorithm you want to run:" << endl << endl;
    cout << "1 - Forward Selection" << endl << "2 - Backward Elimination" << endl << endl;

	int userInput;
    cin >> userInput;

    normalize(fileInput, trainInstances, trainLabels);

    Validator* validator = new Validator(trainInstances, trainLabels);
    Greedy* search = new Greedy(validator);

	vector<Features*> features;

    for(int i = 0; i < trainInstances.at(0).size(); i++) {
        Features* temp = new Features(i + 1);
        features.push_back(temp);
    }

    if (userInput == 1) {
        search -> forwardSelection(features);
    }

    else if (userInput == 2) {
        search -> backwardsElimination(features);
    }

    else {
        cout << "Bad Input" << endl;
        return -1;
    }

    return 0;
} //discussed with Partner Jordan Sam for all files.