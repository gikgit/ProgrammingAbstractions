/*
 * CS 106B Boggle
 * This file declares the graphics support functions for Boggle.
 * The functions appear in a namespace, so to use them, you must write e.g.
 *
 * BoggleGUI::init(4, 4);
 * BoggleGUI::setScore(42, BoggleGUI::HUMAN);
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: Sat 2013/11/09
 * Author : original version by Eric Roberts and Julie Zelenski;
 *          modified substantially by Marty Stepp for Autumn 2013
 */

#ifndef _bogglegui_h
#define _bogglegui_h

#include <string>
#include "gwindow.h"

namespace BoggleGUI {
    /*
     * This enumeration distinguishes the human and computer players.
     */
    enum Player { HUMAN, COMPUTER };

    /*
     * Initializes the Boggle graphics package and its graphics window,
     * using the given number of rows and columns on the board.
     * An error is raised if either dimension is < 0 or > MAX_DIMENSION.
     */
    void initialize(int rowCount, int columnCount);

    /*
     * Returns true if the Boggle GUI has already been initialized.
     */
    bool isInitialized();

    /*
     * Draws the specified letter on the face of the cube at position (row, col).
     * The cubes are numbered from top to bottom left to right starting  with zero.
     * The upper left corner is is (0, 0); the lower right is (rowCount-1, columnCount-1).
     *
     * The highlighted flag makes it possible for you to show which
     * cubes are using when forming a word on the board.
     * If the 'highlighted' flag is true, the cube is drawn with a color highlight;
     * if flag is false, the highlight is removed.
     *
     * An error is raised if row or col is out of range for the board.
     */
    void labelCube(int row, int col, char letter, bool highlighted = false);

    /*
     * Draws the specified letters on the face of all cubes of the board.
     * You can pass a 16-letter string or a string with line breaks after each four.
     * An error is raised if the string is not the right length.
     */
    void labelAllCubes(std::string letters);

    /*
     * Plays a sound effect located in the given file.
     * (NOTE: Sound playing is broken in the current version of the Stanford C++
     *  back-end library, so you probably should not use this function.  Sorry.)
     */
    void playSound(std::string filename);

    /*
     * Records the specified word by adding it to the screen display for
     * the specified player.
     * If the given word has already been recorded, adds it again (so don't do that).
     */
    void recordWord(std::string word, Player player);

    /*
     * Clears the GUI's state, including all letters, highlighting, and scores.
     * After a call to reset(), the cubes will be blank, scores will show as 0,
     * and no words will be recorded.
     */
    void reset();

    /*
     * Sets the Boggle game to pause for the given number of milliseconds
     * after toggling the highlight on any letter cube.
     * If set to <= 0, there will be no delay.
     * The default is 0ms (no delay or animation).
     */
    void setAnimationDelay(int ms);

    /*
     * Sets the score label for the given player to display the given
     * number of points.
     */
    void setScore(int score, Player player);

    /*
     * Sets the Boggle GUI window to display the given text as a status message.
     */
    void setStatusMessage(std::string status);

    /*
     * Closes the GUI window and frees all associated memory.
     */
    void shutdown();
}

#endif
