// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "random.h"
#include "split.h"
#include "tokenscanner.h"
#include "GrammarSolver.h"
#include <iomanip>

using namespace std;

// TODO: write the members
GrammarSolver::GrammarSolver(istream& input){
    string line;
    while(getline(input,line)){
        int wordCount = 0;
        TokenScanner tokens(line);
        tokens.scanStrings();
        tokens.ignoreWhitespace();
        Vector<Vector<string> > rules;
        string nonTerminal;
        while(tokens.hasMoreTokens()) {
            string str = tokens.nextToken();
            if(str!=">"&&str!="<"&&str!=":"&&str!="="&&str!="|"){
                wordCount++;
                if(wordCount==1) {
                    nonTerminal = str;
                    Vector<string> rule;
                    rules.add(rule);
                    Grammar.put(nonTerminal,rules);
                }
                if(wordCount>1)
                    Grammar[nonTerminal][ Grammar[nonTerminal].size()-1].add(str);
            }

            if(str=="|"){
                Vector<string> rule;
                Grammar[nonTerminal].add(rule);
            }
        }
    }
}

bool GrammarSolver::contains(string symbol){
    for(string nonTerminal:Grammar){
        if(symbol==nonTerminal) return true;
    }
    return false;
}

string GrammarSolver::generate(string symbol){
    if(!contains(symbol)) return symbol;
    else{
        int rule = randomInteger(0,Grammar[symbol].size()-1);
        int size = Grammar[symbol][rule].size();
        string result;
        for(int i=0; i<size; i++){
            result += " ";
            result += generate(Grammar[symbol][rule][i]);
        }
        return result;
    }
}

void GrammarSolver::getSymbols(Set<string>& out){
     for(string nonTerminal:Grammar){
         out.add(nonTerminal);
     }
}
