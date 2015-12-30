// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
// TODO: include any other header files you need (e.g. Stanford collections)
#include "grid.h"
#include "lexicon.h"


using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    // TODO: decide the public member functions and declare them
    Boggle();
    void randomSetUp();
    void manualSetUp(string& sequence);
    void print();
    bool containInDict(string word);
    bool containPrefix(string word);
    bool visited(int i, int j);
    void setVisited(int i, int j);
    void setUnvisited(int i, int j);
    char getBoard(int i, int j);
    bool isOutOfBorder(int i, int j);
    void resetMark();


private:
    // TODO: decide the private member variables/functions and declare them
    Grid<char> board;
    Grid<bool> mark;
    Lexicon dict;
};

#endif
