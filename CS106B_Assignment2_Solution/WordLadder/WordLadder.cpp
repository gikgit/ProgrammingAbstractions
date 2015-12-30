/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"

using namespace std;

void printSolution(Vector<string> & solution);

int main() {
	// [TODO: fill in the code]
    Lexicon english("EnglishWords.dat");
    Queue<Vector<string> > ladders;
    cout << "Enter start word (RETURN to quit): ";
    string startWord = getLine();
    cout << "Enter destination word: ";
    string destinationWord = getLine();
    bool findSolution = false;
    
    // initialize
    Lexicon usedWords;
    Vector<string> ladder;
    ladder.add(startWord);
    ladders.enqueue(ladder);
    usedWords.add(startWord);
    
    //
    while (!ladders.isEmpty()) {
        ladder = ladders.dequeue();
        if(ladder[ladder.size()-1]==destinationWord) {
            printSolution(ladder);
            findSolution = true;
            break;
        }
        for (int i=0; i<ladder.get(ladder.size()-1).length(); i++) {
            for (char ch='a'; ch<='z'; ch++) {
                string newWord = ladder.get(ladder.size()-1);
                newWord[i] = ch;
                if(!usedWords.contains(newWord) && english.contains(newWord)) {
                    Vector<string> newLadder = ladder;
                    newLadder.add(newWord);
                    ladders.enqueue(newLadder);
                    usedWords.add(newWord);
                }
            }
        }
    }
    
    if(!findSolution) cout << "no word ladder exists.";
    
    return 0;
}


void printSolution(Vector<string> & ladder){
    cout << "Found ladder: ";
    for (int i=0; i<ladder.size()-1; i++) {
        cout << ladder[i] << "->";
    }
    cout << ladder[ladder.size()-1];
}

