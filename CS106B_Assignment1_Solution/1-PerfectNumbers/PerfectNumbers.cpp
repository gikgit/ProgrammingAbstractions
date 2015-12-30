/*
 * File: PerfectNumbers.cpp
 * ------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the perfect number problem.
 * [TODO: rewrite the documentation]
 */

//#include "cs106/genlib.h"
#include <iostream>

using namespace std;

const int MAX = 10000;
const int MIN = 1;

bool IsPerfect(int number);

int main() {
	// [TODO: fill in the code]
	cout << "The perfect numbers in the range of 1 to 10000 are: " << endl;
	for (int i=MIN; i<MAX; i++) 
		if(IsPerfect(i)) cout << i << endl;
	return 0;
}


bool IsPerfect(int number) {
	int sum = 0;
	for (int i=1; i<=number/2; i++) 
		if(number%i==0) sum += i;
	if (sum==number) return true;
	return false;
}
