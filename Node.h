#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include "Validator.h"

using namespace std;
//nodes are subsets of features, features are whatever data type is in the input file (doubles?)

class Features {
    public:
        int data;
        Features(int data) {
        this -> data = data;
        }
};

class Node {
	public:
		double score;
		vector<Features*> nodeFeatures;
		vector<Node*> children;
		Validator* validator;

		Node(Validator* validator){this->validator = validator;};

		Node(vector<Features*> features, Validator* validator){
			for (int i = 0; i < features.size(); i++){
				this->nodeFeatures.push_back(features.at(i));
			}
			this->validator = validator;
    	}

		double evaluator(){
			vector<int> accuracy;
			double temp = 0;
			for (int i = 0; i < nodeFeatures.size(); i++) {
				int val = nodeFeatures.at(i)->data;
				accuracy.push_back(val);
			}
			temp = this -> validator -> leaveOneOutValidation(accuracy);
			return this -> score = temp * 100.0;
    	}

		void printFeatures(){
			cout << "{";
        	for (int i = 0; i < nodeFeatures.size()-1; i++){
            	cout << nodeFeatures.at(i)->data << ",";
       		}
			cout << nodeFeatures.at(nodeFeatures.size()-1)->data << "}";
		}
};
#endif