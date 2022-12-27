#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

class Classifier {
    public:
        vector<vector<double>> trainingInstances;
        vector<double> trainingLabels;

        Classifier() {}
		double euclideanDist(vector<double> l, vector<double> r){
			double sum = 0;
			for (int i = 0; i < l.size(); i++){
				sum += pow((l.at(i) - r.at(i)), 2);
			}
			return sqrt(sum);
        }

        void train(vector<vector<double>> trainingInstances, vector<double> trainingLabels) {
            this->trainingInstances = trainingInstances;
            this->trainingLabels = trainingLabels;
        }

        double test(vector<double> testingInstance) {
            double prediction = INT_MAX;
            double nearestNeighbor = INT_MAX;
        
            for (int i = 0; i < trainingInstances.size(); i++) {
                double distance = euclideanDist(trainingInstances.at(i), testingInstance);

                if (nearestNeighbor > distance) {
                    nearestNeighbor = distance;
                    prediction = trainingLabels.at(i);
                }
            }
            return prediction;
        }
};
#endif