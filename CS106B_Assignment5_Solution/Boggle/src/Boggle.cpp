// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "lexicon.h"
#include "cassert"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[16] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// TODO: implement the members you declared in Boggle.h
Boggle::Boggle() {
    board.resize(BOARD_SIZE,BOARD_SIZE);
    mark.resize(BOARD_SIZE,BOARD_SIZE);
    dict.addWordsFromFile(DICTIONARY_FILE);
}

void Boggle::randomSetUp() {
    int index1 = 0;
    for(int i=0;i<board.numRows();i++){
        for(int j=0;j<board.numCols();j++){
            int index2 = randomInteger(0,CUBE_SIDES-1);
            board.set(i,j,CUBES[index1][index2]);
            mark.set(i,j,false);
            index1++;
        }
    }
}

void Boggle::manualSetUp(string& sequence){
    int index = 0;
    for(int i=0;i<board.numRows();i++){
        for(int j=0;j<board.numCols();j++){
            board.set(i,j,sequence[index]);
            mark.set(i,j,false);
            index++;
        }
    }
}

void Boggle::print(){
    for(int i=0;i<board.numRows();i++){
        for(int j=0;j<board.numRows();j++){
            cout << board.get(i,j);
        }
        cout << '\n';
    }
}

bool Boggle::containInDict(string word) {
    assert(!dict.isEmpty());
    return dict.contains(word);
}

bool Boggle::containPrefix(string word) {
    assert(!dict.isEmpty());
    return dict.containsPrefix(word);
}

bool Boggle::visited(int i, int j){
    return mark.get(i,j);
}

void Boggle::setVisited(int i, int j) {
    mark.set(i,j,true);
}

void Boggle::setUnvisited(int i, int j) {
    mark.set(i,j,false);
}

char Boggle::getBoard(int i, int j){
    return board.get(i,j);
}

bool Boggle::isOutOfBorder(int i, int j){
    return !board.inBounds(i,j);
}

void Boggle::resetMark(){
    for(int i=0;i<board.numRows();i++){
        for(int j=0;j<board.numRows();j++){
            mark.set(i,j,false);
        }
    }
}



