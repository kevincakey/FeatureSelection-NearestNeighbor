#ifndef DATANORMALIZER_H
#define DATANORMALIZER_H
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

double stringToDouble(string& input) {                                

    double base = stod(input.substr(0, input.find('e'))); 
    int exp  = stoi(input.substr(input.find('e') + 1, 4));

    if (exp <= 0) {     
        for (int i = exp; i < 0; i++) { 
            base = base / 10;
        }
    }
    else { 
        for (int i = 0; i < exp; i++) {
            base = base * 10;
        }
    }
    return base;
}

void normalize(string fileInput, vector<vector<double>>& trainingInstances, vector<double>& trainingLabels) {
    ifstream ifs;
    ifs.open(fileInput);

	if (!ifs.is_open()){
		cout << "Can't open " << fileInput << endl;
		exit(0);
	}

    if (ifs.is_open()){
        stringstream iss;
        string row;
        while(getline(ifs, row)){
            iss << row;
            string temp;
            iss >> temp;
            trainingLabels.push_back(stringToDouble(temp));

            vector<double> features;
            while (iss >> temp) {
                features.push_back(stringToDouble(temp));
            }
            trainingInstances.push_back(features);

            features.clear();
            iss.clear();
        }

		cout << "This dataset has " << trainingInstances.at(0).size() << " features (not including the class attribute), with " << trainingLabels.size() << " instances." << endl;

		cout << "Please wait while I normalize the data..." << endl;

		vector<double> average(trainingInstances.at(0).size(), 0.0);
		vector<double> std_dev(trainingInstances.at(0).size(), 0.0);
		
		for (int i = 0; i < trainingInstances.size(); i++){
			for (int j = 0; j < trainingInstances.at(i).size(); j++) {
				average.at(j) += trainingInstances.at(i).at(j);
			}
		}
		for (int i = 0; i < average.size(); i++){
			average.at(i) = average.at(i) / trainingInstances.size();
		}
		
		for (int i = 0; i < trainingInstances.size(); i++){
			for (int j = 0; j < trainingInstances.at(i).size(); j++) {
				std_dev.at(j) += pow((trainingInstances.at(i).at(j) - average.at(j)), 2);
			}
		}
		for (int i = 0; i < std_dev.size(); i++) {
			std_dev.at(i) = sqrt(std_dev.at(i) / trainingInstances.size());
		}
		
		for (int i = 0; i < trainingInstances.size(); i++){
			for (int j = 0; j < trainingInstances.at(i).size(); j++) {
				trainingInstances.at(i).at(j) = (trainingInstances.at(i).at(j) - average.at(j)) / std_dev.at(j);
			}
		}
		cout <<"   Done!" << endl <<endl;
    }
	//https://www.tutorialspoint.com/mean-and-median-of-a-matrix-in-cplusplus
	//https://www.tutorialspoint.com/cplusplus-program-to-calculate-standard-deviation
	//https://www.statology.org/z-score-normalization/
}
#endif