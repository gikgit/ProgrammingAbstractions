/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the coin-flipping problem.
 * [TODO: rewrite the documentation]
 */


#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool Consecutive3Heads(vector<string> & flipCoin);
bool RandomChance(float p);

int main() {
	// [TODO: fill in the code]
	vector<string> flipCoin;
	srand (time(NULL));

	while(true){
		if(RandomChance(0.5)) {
			flipCoin.push_back("tails");
			cout << "tails" << endl;
		}
		else {
			flipCoin.push_back("heads");
			cout << "heads" << endl;
		}
		if(flipCoin.size()>=3) {
			if(Consecutive3Heads(flipCoin)) break;
		}
	}
	
	cout << "It took" << " " << flipCoin.size() << " " << "flips to get 3 consecutive heads.";
	return 0;
}


bool RandomChance(float p){
	if (float(rand() % 10 + 1) / 10 > p) return true;
	else return false;
}

bool Consecutive3Heads(vector<string> & flipCoin){
	int size = flipCoin.size();
	if(flipCoin[size-1]=="heads"&&flipCoin[size-2]=="heads"&&flipCoin[size-3]=="heads"){
		return true;
	}
	else return false;
}