// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef _grammarsolver_h
#define _grammarsolver_h

#include <fstream>
#include <iostream>
#include <string>
#include "hashmap.h"
#include "map.h"
#include "set.h"
#include "vector.h"

using namespace std;

class GrammarSolver {
public:
    GrammarSolver(istream& input);
    bool contains(string symbol);
    string generate(string symbol);
    void getSymbols(Set<string>& out);

    Map<string, Vector<Vector<string> >> Grammar;
};

#endif
