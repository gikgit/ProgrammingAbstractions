/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the combinations problem.
 * [TODO: rewrite the documentation]
 */

// #include "genlib.h"
// #include "simpio.h"
#include <iostream>
#include <iomanip>

using namespace std;

int PascalTriangle(int n, int k);

int main() {
	// [TODO: fill in the code]
	cout << "n? ";
	int n;
	cin >> n;
	for (int i=0; i<n; i++) {
		for (int j=0; j<=i; j++) {
			cout << setw(4) << "(" << i << "," << j << ")";
		}
		cout << "\n";
	}
	
	cout << "\n";
	cout << "\n";
	
	for (int i=0; i<n; i++) {
		for (int j=0; j<=i; j++) {
			cout << setw(8)<< PascalTriangle(i,j);
		}
		cout << "\n";
	}
	return 0;
}


int PascalTriangle(int n, int k) {
	if(k==0||k==n) return 1;
	else {
		return PascalTriangle(n-1,k-1) + PascalTriangle(n-1,k);
	}

}