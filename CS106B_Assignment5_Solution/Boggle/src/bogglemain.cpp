/*
 * CS 106B Boggle
 * This file contains the main program and user interface for running your
 * Boggle game.  We provide you a skeleton of this file that contains a shell
 * of the overall logic, but you must complete the playOneGame function.
 *
 * The playOneGame function talks to the Boggle class that you will write.
 * This file should contain all user interaction (cout / cin), while the Boggle
 * class should contain ALL game state such as the 16 letter cubes, the set of
 * words that have been formed, the algorithms for searching for words, etc.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: Sat 2013/11/09
 * Author : Marty Stepp
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "Boggle.h"
#include "bogglemain.h"
#include "bogglegui.h"
using namespace std;

int main() {
    intro();

    // play games repeatedly until user decides to quit
    Boggle boggle;
    while (true) {
        playOneGame(boggle);
        cout << endl;
        if (!yesOrNo("Play again (Y/N)? ")) {
            break;
        }
    }

    cout << "Have a nice day." << endl;
    BoggleGUI::shutdown();
    return 0;
}

/*
 * Sets up the output console and explains the program to the user.
 */
void intro() {
    setConsoleSize(850, 550);
    setConsoleFont("Monospaced-Bold-18");
    setConsoleEcho(true);
    // setConsolePrintExceptions(true);

    cout << "Welcome to CS 106B Boggle!" << endl;
    cout << "This game is a search for words on a 2-D board of letter cubes." << endl;
    cout << "The good news is that you might improve your vocabulary a bit." << endl;
    cout << "The bad news is that you're probably going to lose miserably to" << endl;
    cout << "this little dictionary-toting hunk of silicon." << endl;
    cout << "If only YOU had a gig of RAM!" << endl;
    cout << endl;
    getLine("Press Enter to begin the game ... ");
}

/*
 * Prompts the user to answer a yes/no question and returns true if the user
 * typed 'yes' (or anything that starts with a 'y', case-insensitively),
 * false if the user types anything that starts with 'n', or re-prompts if
 * the user doesn't type a 'y' or 'n' word.
 */
bool yesOrNo(string prompt) {
    while (true) {
        string answer = trim(toLowerCase(getLine(prompt)));
        if (startsWith(answer, 'y')) {
            return true;
        } else if (startsWith(answer, 'n')) {
            return false;
        } else {
            cout << "Please type a word that begins with 'y' or 'n'." << endl;
        }
    }
}
