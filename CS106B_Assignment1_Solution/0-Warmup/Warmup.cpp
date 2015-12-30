/*
 * File: Warmup.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This program generates a hash code based on user's name.
 * As given, this code has two compiler errors you need to track down 
 * and fix in order to get the program up and running.
 * [Originally written by Julie Zelenski]
 */

//#include "genlib.h"
//#include "simpio.h"
#include <iostream>

using namespace std;
/* Constants */

const int MAX_HASH_CODE = 10000;        // Upper bound for hash codes
const long MULTIPLIER = -1664117991L;   // Parameter used in Hash function

/* Function prototypes */

int Hash(string key, int maxCode);

/*
 * Function: Hash
 * Usage: code = Hash(key, maxCode);
 * ---------------------------------
 * This function takes the key and uses it to derive a hash code,
 * which is an integer in the range [0, maxCode - 1].  The hash
 * code is computed using a method called linear congruence.
 */

int Hash(string s, int maxCode) {
	unsigned long hashcode = 0;
	for (int i = 0; i < s.length(); i++) {
		hashcode = hashcode * MULTIPLIER + s[i];
	}
	return (hashcode % maxCode);
}

/* Main program to test the Hash function */

int main() {
	cout << "Please enter your name: ";
	string name;
	cin >> name;
	int hashcode = Hash(name,MAX_HASH_CODE);
	cout << "The hash code for your name is " << hashcode << "." << endl;
	return 0;
}
