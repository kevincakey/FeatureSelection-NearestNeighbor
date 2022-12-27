#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <vector>
#include <string>
#include "Classifier.h"

using namespace std;

class Validator {
    public:
        vector<vector<double>> instances;
        vector<double> labels;
        Classifier* classifier;

    public:
        Validator(vector<vector<double>> instances, vector<double> labels) {
            this->classifier = new Classifier();
            this->instances = instances;
            this-> labels = labels;
        }

        double leaveOneOutValidation(vector<int> featureSubset) {

            vector<vector<double>> passedInstances;

            for (int i = 0; i < instances.size(); i++) {
                vector<double> temp;
                for (int j = 0; j < featureSubset.size(); j++) {
                    temp.push_back(instances.at(i).at(featureSubset.at(j) - 1));
                }
                passedInstances.push_back(temp);
            }
            double counter = 0.0; //changed to double

            for (int i = 0; i < instances.size(); i++) {

                vector<vector<double>> toTrain = passedInstances;
                vector<double> kFoldLabels = labels;

                toTrain.erase(toTrain.begin() + i);
                kFoldLabels.erase(kFoldLabels.begin() + i);
                
                vector<double> toTest = passedInstances.at(i);
                double testLabel = labels.at(i);
                
                classifier -> train(toTrain, kFoldLabels);                   

                double classification = classifier -> test(toTest);
                
                if (classification == testLabel) { 
                    counter++;
                }
            }
            return counter / (double)(instances.size());
        }
};
#endif