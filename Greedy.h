#ifndef GREEDY_H
#define GREEDY_H

#include <iostream>
#include <vector>
#include "Node.h"
#include "Validator.h"

using namespace std;

class Greedy {
    private:
        Node* head;
		Validator* validator;
	public: 
		Greedy(Validator* validator) {
			this->head = nullptr;
			this -> validator = validator;
		}

		void forwardSelection(vector<Features*> features){
			this->head = new Node(this->validator);
			Node* curr = this->head;
			curr->score = evaluate(curr);
			cout << "Running nearest neighbor with no features (default rate), using \"leaving-one-out\" evaluation, I get an accuracy of " << head->score << '%' << endl << endl;
			cout << "Beginning search" << endl << endl;

			while(!features.empty()){

				for(int i = 0; i<features.size(); i++){
					Node* temp = new Node(curr->nodeFeatures, this->validator);
					temp->nodeFeatures.push_back(features[i]);
					temp -> evaluator();
					curr->children.push_back(temp);
				}

				double bestAccuracy = 0.0;
				double bestAccuracyIndex = 0.0;
				for(int i =0; i < curr->children.size(); i++){
					double currAccuracy = curr->children[i]->score;
					cout << "Using feature(s) ";
					curr->children[i]->printFeatures();
					cout << " accuracy is " << currAccuracy << "%" <<endl;
					if(bestAccuracy < currAccuracy){
						bestAccuracyIndex = i;
					}
					bestAccuracy = max(bestAccuracy, currAccuracy);   
				}

				if(curr->score > bestAccuracy){
					cout << endl << "(Warning, Accuracy has decreased!)" << endl;
                    cout << "Finished Search, best feature subset is ";
                    curr -> printFeatures();
                    cout << ", which has an accuracy of " << curr -> score << '%' << endl;
					return;
				}

				cout << endl << "Feature set ";
				curr->children.at(bestAccuracyIndex)->printFeatures(); 
				cout << " was best, accuracy is " << curr->children.at(bestAccuracyIndex)->score << '%' << endl << endl;

				features.erase(features.begin() + bestAccuracyIndex);
				curr = curr -> children.at(bestAccuracyIndex);
			}
			cout << "Finished Search!! The best feature subset is ";
            curr -> printFeatures();
            cout << ", which has an accuracy of " << curr -> score << '%' << endl;

            return;
		}

		void backwardsElimination(vector<Features*> features){ 
			this->head = new Node(features, this->validator);
			Node* curr = this->head;
			curr->score = evaluate(curr);
			cout << "Running Nearest Neighbor with all features and \"leaving-one-out\" evaluation, I get an accuracy of " << head->score << '%' << endl << endl;
			cout << "Beginning search" << endl << endl;

			while(!curr->nodeFeatures.empty()){

				for(int i = 0; i<features.size(); i++){
					curr->children.push_back(removeFeature(curr, i));
				}

				double bestAccuracy = 0.0;
				double bestAccuracyIndex = 0.0;
				for(int i =0; i < curr->children.size(); i++){
					if (!(curr->nodeFeatures.size() == 1)) {
						double currAccuracy = curr->children[i]->score;
						cout << "Using feature(s) ";
						curr->children[i]->printFeatures();
						cout << " accuracy is " << currAccuracy << "%" <<endl;
						if(bestAccuracy < currAccuracy){
							bestAccuracyIndex = i;
						}
						bestAccuracy = max(bestAccuracy, currAccuracy);  
					}
				}

				if(curr->score > bestAccuracy){
					cout << endl << "(Warning, Accuracy has decreased!)" << endl;
                    cout << "Finished Search, best feature subset is ";
                    curr -> printFeatures();
                    cout << ", which has an accuracy of " << curr -> score << '%' << endl;
					return;
				}

				cout << endl << "Feature set ";
				curr->children.at(bestAccuracyIndex)->printFeatures(); 
				cout << " was best, accuracy is " << curr->children.at(bestAccuracyIndex)->score << '%' << endl << endl;

				features.erase(features.begin() + bestAccuracyIndex);
				curr = curr -> children.at(bestAccuracyIndex);
			}
			cout << "Finished Search!! The best feature subset is ";
            curr -> printFeatures();
            cout << ", which has an accuracy of " << curr -> score << '%' << endl;

            return;
		}

		Node* removeFeature(Node* n, int i) {
            Node* temp = new Node(n->nodeFeatures, this->validator);
            temp->nodeFeatures.erase(temp->nodeFeatures.begin() + i);
			temp -> evaluator();
            return temp;
        }

		double evaluate(Node* n){
			return rand() % 100;
		}
	};
#endif