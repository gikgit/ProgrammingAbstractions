// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "console.h"
#include "simpio.h"
#include "strlib.h"
// TODO: include any other header files you need
#include "set.h"
#include "foreach.h"

void playOneGame(Boggle& boggle);
void boardSetUp(Boggle& boggle);
bool isAllUpperCase(string sequence);
void allWords(Boggle &boggle, Set<string>& set);
bool findAllWords(string word, Set<string>& set, Boggle& boggle, int i, int j);
void userPlay(Boggle& boggle, int& userScore,Set<string>& userGuessed);
void computerPlay(Boggle& boggle, int& computerScore,
                  Set<string>& userGuessed, Set<string>& computerGuessed);
bool isValid(string word, Set<string>& wordsGussed, Boggle& boggle, Set<string>& set);
void computeScore(Set<string>& userGuessed, int& score);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)

    boardSetUp(boggle);

    int userScore = 0, computerScore = 0;
    Set<string> userGuessed, computeGuessed;

    userPlay(boggle,userScore,userGuessed);
    cout << "It's my turn!"<< endl;
    computerPlay(boggle,computerScore,userGuessed,computeGuessed);

    if(userScore>computerScore)
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny computer!";
    else
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!";


}

void boardSetUp(Boggle& boggle){
    string option;
    while(true){
        cout << "Do you want to generate a random board? ";
        getline(cin,option);
        if(option=="Y"||option=="y") {
            boggle.randomSetUp();
            cout << "It's your turn!"<< endl;
            boggle.print();
            break;
        }
        else if(option=="N"||option=="n"){
            string sequence;
            cout << "input your strings: ";
            getline(cin,sequence);
            while(sequence.length()!=16||!isAllUpperCase(sequence)){
                cout << "it needs 16 characters and all uppercase,"<< '\n'
                     <<"input your strings again: ";
                getline(cin,sequence);
            }
            boggle.manualSetUp(sequence);
            boggle.print();
            break;
        }
        else cout << "please input Y/y or N/n: " << endl;
    }
}

void userPlay(Boggle& boggle, int& userScore, Set<string>& userGuessed) {
    Set<string> set;
    boggle.resetMark();
    allWords(boggle,set);

    string word;
    while(true){
        cout << '\n';
        cout << "Your words " << '(' << userGuessed.size() << ')' << ':';
        cout << '{';
        foreach(string word in userGuessed) {
            cout << word + " ";
        }
        cout << '}' << endl;
        cout << "Your score: "<< userScore << endl;
        cout << "Type a word (or press Enter to end your turn):";
        getline(cin, word);
        if(word=="") break;
        word = toUpperCase(word);
        if(isValid(word,userGuessed,boggle,set)) {
            cout << "You found a new word " << word ;
            userGuessed.add(word);
        }
        else cout << "not a valid word";
        computeScore(userGuessed,userScore);
    }
    cout << '\n';


}

void computerPlay(Boggle& boggle,
                  int& computerScore,
                  Set<string>& userGuessed,
                  Set<string>& computerGuessed)
{
    Set<string> set;
    boggle.resetMark();
    allWords(boggle,set);
    computerGuessed = set - userGuessed;
    cout << '\n';
    cout << "My words " << '(' << computerGuessed.size() << ')' << ':';
    cout << '{';
    foreach(string word in computerGuessed) {
        cout << word + " ";
    }
    cout << '}' << endl;
    computeScore(computerGuessed,computerScore);
    cout << "My score: "<< computerScore << endl;

}

void computeScore(Set<string>& userGuessed, int& score){
    score = 0;
    foreach(string word in userGuessed){
        if(word.length()>=4) score = score + (word.length()-3);
    }
}

bool isAllUpperCase(string sequence) {
    for(int i=0; i<sequence.length(); i++){
        if(islower(sequence[i])) return false;
    }
    return true;
}

bool isValid(string word, Set<string>& wordsGussed, Boggle& boggle, Set<string>& set) {
    return word.length()>=4&&
           !wordsGussed.contains(word)&&
           boggle.containInDict(word)&&
           set.contains(word);
}

bool findAllWords(string word, Set<string>& set, Boggle& boggle, int i, int j) {
    if(boggle.isOutOfBorder(i,j)) return false;
    if(boggle.visited(i,j)) return false;
    boggle.setVisited(i,j);
    word += boggle.getBoard(i,j);
    if(boggle.containInDict(word)){
        if(word.length()>=4) set.add(word);
    }
    if(boggle.containPrefix(word)){
        for(int k=i-1; k<=i+1; k++) for(int m=j-1; m<=j+1; m++){
            if(findAllWords(word, set, boggle, k, m)) return true;
        }
    }
    word.erase(word.length()-1,1);
    boggle.setUnvisited(i,j);
    return false;
}

void allWords(Boggle& boggle, Set<string>& set){
    for(int i=0;i<boggle.BOARD_SIZE;i++){
        for(int j=0;j<boggle.BOARD_SIZE;j++) {
            string word = "";
            if(findAllWords(word, set, boggle, i, j))
                continue;
        }
    }
}
