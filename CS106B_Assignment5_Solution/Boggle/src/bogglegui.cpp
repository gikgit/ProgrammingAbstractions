/*
 * CS 106B Boggle
 * This file implements the graphics support functions for Boggle.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Version: Tue 2013/11/12
 * Author : original version by Eric Roberts and Julie Zelenski;
 *          modified by Marty Stepp for Autumn 2013
 */

/*
 * General implementation notes
 * ----------------------------
 * This file implements the graphics support functions for the Boggle
 * program.  It makes straightforward use of the extended graphics
 * library to draw the cubes, board, letters, scoreboard, etc. The
 * implementations of the individual functions are fairly simple
 * and many of the helper functions do not require individual comments.
 * For descriptions of the behavior of the exported functions,
 * please see the interface file.
 */

#include <string>
#include "bogglegui.h"
#include "error.h"
#include "filelib.h"
#include "gobjects.h"
#include "grid.h"
#include "gtypes.h"
#include "gwindow.h"
#include "sound.h"
#include "strlib.h"

namespace BoggleGUI {
    /*
     * Constants
     * ---------
     * To configure fixed spacing, fonts, etc.
     */
    const int MAX_DIMENSION = 6;
    const int BOGGLE_WINDOW_WIDTH = 800;
    const int BOGGLE_WINDOW_HEIGHT = 450;
    const double DEFAULT_ANIMATION_DELAY = 0;

    // const double EPSILON = 0.0001;         // constant for antialiasing
    const double EPSILON = 0.0;            // constant for antialiasing
    const double BOARD_BORDER = 8;         // width of border around the cubes
    const double INDENT = 20;              // indent at vertical edges of window
    const double LABEL_HEIGHT = 40;        // space at top of window for labels
    const double LABEL_DY = -5;            // adjustment for label text
    const double WORD_DY = 2;              // adjustment for word list
    const double HUMAN_PERCENTAGE = 0.38;  // percentage of space for word lists
                                           // to apportion to human
    const string CUBE_FONT = "Helvetica";  // Font for letters on cube face
    const double FONT_PERCENTAGE = 0.6;    // percentage of cube used for letter
    const string SCORE_FONT = "Helvetica"; // Font for scoreboard names & scores
    const int SCORE_FONT_SIZE = 18;
    const int WORD_FONT_SIZE = 11;

    #ifdef _MSC_VER
    const string WORD_FONT = "Arial";
    #else
    const string WORD_FONT = "Geneva";
    #endif

    // colors used on the GUI, as hex strings
    const string BOARD_COLOR    = "#023BD6";
    const string DIE_COLOR      = "#E6E6E6";
    const string LETTER_COLOR   = "#023BD6";
    const string DIE_COLOR_H    = "#FFEE66";   // _H = highlighted colors
    const string LETTER_COLOR_H = "#E6E6E6";
    const string WORD_COLOR     = "#02805D";
    const string LABEL_COLOR    = "#028040";

    /*
     * A static struct is used to gather the state that is local to this module.
     * Mostly this is geometry calculated to fit the cubes, word lists,
     * and labels neatly within the current size of the graphics window.
     * In addition, the module tracks the count of words listed for each player
     * (to place additional words in the correct location in the displayed word
     * list) and the scores for each player (which must be saved and erased
     * before updating). There is also a 2-d array of the letters currently
     * showing on the cubes, to enable drawing them inverted for the
     * highlighting function.
     *
     * We'd like to use GRectangle instead, but it doesn't support setter methods.
     */
    struct RectStruct { double x, y, w, h; };
    static struct {
        int wordCount[2];         // words displayed for each player
        RectStruct scoreBox[2];   // rectangle enscribing label + score for each player
        RectStruct statusBox;     // rectangle enscribing current game status
        double wordColumnWidth;   // width of word list columns
        double cubeSize;          // size of cube
        double fontSize;          // font size used for labeling cubes
        RectStruct board;         // rectangle enscribed the cubes
        int rowCount;             // dimensions of cube layout on board
        int columnCount;
    } gState;

    // Global pointer to the graphics window
    static GWindow *gwp = NULL;
    static GLabel *humanScoreLabel = NULL;
    static GLabel *computerScoreLabel = NULL;
    static GLabel *statusLabel = NULL;
    static int animationDelay = DEFAULT_ANIMATION_DELAY;

    /*
     * These are the prototypes for functions private to this module.  These
     * helper functions are used to implement the functions which are exported
     * from this module (see .h for prototypes of the exported functions)
     */
    static void calculateGeometry(int rowCount, int columnCount);
    static double cubeX(int col);
    static double cubeY(int row);
    static void drawAndFillRoundedRect(double x, double y, double width, double height, double r, string color);
    static void drawCenteredChar(double centerX, double centerY, char ch);
    static void drawCube(int row, int col, char ch, bool highlight);
    static void drawEmptyCubes();
    static void drawOneScore(Player player, int value);
    static void drawPlayerLabel(Player player, string name);
    static void drawRoundedRect(double x, double y, double width, double height, double r);
    static void ensureInitialized();
    static void eraseOldScore(Player player);
    static void fillBox(double x, double y, double width, double height, string color);
    static void fillRoundedRect(double x, double y, double width, double height, double r, string color);

    void initialize(int rowCount, int columnCount) {
        if (rowCount < 0 || rowCount > MAX_DIMENSION
                        || columnCount < 0 || columnCount > MAX_DIMENSION) {
            error("init called with invalid dimensions.");
        }
        if (!isInitialized()) {
            gwp = new GWindow(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
            gwp->setWindowTitle("CS 106B Boggle");
            gState.rowCount = rowCount;
            gState.columnCount = columnCount;
            calculateGeometry(rowCount, columnCount);
        }
        reset();
    }

    bool isInitialized() {
        return gwp != NULL;
    }

    void labelAllCubes(string letters) {
        ensureInitialized();
        if ((int) letters.length() < gState.rowCount * gState.columnCount) {
            error("labelCubes called with too-short letters string: \"" + letters + "\"");
        }
        int row = 0;
        int col = 0;
        bool labeledAll = false;
        for (int i = 0; i < (int) letters.length(); i++) {
            char letter = letters[i];
            if (!isalpha(letter)) {
                continue;
            }
            labelCube(row, col, letter);
            col++;
            if (col == gState.columnCount) {
                col = 0;
                row++;
                if (row == gState.rowCount) {
                    labeledAll = true;
                    break;
                }
            }
        }
        if (!labeledAll) {
            error("labelCubes didn't label every cube from letters string: \"" + letters + "\"");
        }
    }

    void labelCube(int row, int col, char letter, bool highlighted) {
        ensureInitialized();
        if (row < 0 || row >= gState.rowCount || col < 0 || col >= gState.columnCount) {
            error(string("labelCube called with invalid row, col arguments.  Must be between (0, 0) and (")
                  + integerToString(gState.rowCount) + ", " + integerToString(gState.columnCount) + ")");
        }
        if (!isalpha(letter) && letter != ' ') {
            error(string("labelCube called with non-alphabetic character: '") + letter);
        }
        drawCube(row, col, toupper(letter), highlighted);
        if (highlighted && animationDelay > 0) {
            pause(animationDelay);
        }
    }

    void playSound(string filename) {
        Sound s(filename);
        s.play();
    }

    void recordWord(string word, Player player) {
        ensureInitialized();
        if (player != HUMAN && player != COMPUTER) {
            error("recordWord called with invalid player argument.");
        }
        word = toLowerCase(word);
        GLabel *lab = new GLabel(word);
        lab->setFont(WORD_FONT + "-" + integerToString(WORD_FONT_SIZE));
        lab->setColor(WORD_COLOR);
        int wordCountInRow = int(gState.scoreBox[player].w/gState.wordColumnWidth);
        int row = gState.wordCount[player] / wordCountInRow;
        int col = gState.wordCount[player] % wordCountInRow;
        gState.wordCount[player]++;
        gwp->add(lab, gState.scoreBox[player].x + col * gState.wordColumnWidth,
                      gState.scoreBox[player].y + (row + 1) * WORD_FONT_SIZE + WORD_DY);
        if (col == wordCountInRow - 1) gwp->repaint();
    }

    void reset() {
        ensureInitialized();
        gState.wordCount[HUMAN] = 0;
        gState.wordCount[COMPUTER] = 0;
        gwp->clear();
        fillBox(gState.board.x, gState.board.y, gState.board.w, gState.board.h, BOARD_COLOR);
        drawEmptyCubes();
        drawPlayerLabel(HUMAN, "Human");
        drawPlayerLabel(COMPUTER, "Computer");
        drawOneScore(HUMAN, 0);
        drawOneScore(COMPUTER, 0);
    }

    void setAnimationDelay(int ms) {
        animationDelay = ms;
    }

    void setScore(int points, Player player) {
        ensureInitialized();
        eraseOldScore(player);
        drawOneScore(player, points);
    }

    void setStatusMessage(std::string status) {
        ensureInitialized();
        if (statusLabel != NULL) {
            gwp->remove(statusLabel);
        }

        // BUGBUG: must remove quotation marks from the string to fix bug
        //         in Stanford C++ back-end -- Marty
        if (status.find("\"") != string::npos) {
            ostringstream os;
            for (int i = 0; i < (int) status.length(); i++) {
                if (status[i] == '"') {
                    os << "\\\"";
                } else {
                    os << status[i];
                }
            }
            status = os.str();
        }

        statusLabel = new GLabel(status);
        statusLabel->setFont(SCORE_FONT + "-" + integerToString(SCORE_FONT_SIZE));
        statusLabel->setColor(LABEL_COLOR);
        gwp->add(statusLabel, gState.statusBox.x, gState.statusBox.y);
    }

    void shutdown() {
        if (isInitialized()) {
            gwp->setVisible(false);
            gwp->close();
            delete gwp;
            exitGraphics();
        }
    }

    /*
     * Handy utility functions to return coordinates of the lower-left
     * corner of the cube at position (row, col).  The cubes are numbered
     * from top to bottom, left to right starting from zero. Therefore,
     * the upper left corner is (0,0), lower right is (rowCount-1,columnCount-1)
     */
    static double cubeX(int col) {
        return gState.board.x + BOARD_BORDER/2.0 + gState.cubeSize*col + EPSILON;
    }
    static double cubeY(int row) {
        return gState.board.y + BOARD_BORDER/2.0 + gState.cubeSize*row + EPSILON;
    }

    /* Function: calculateGeometry
     * ---------------------------
     * This internal helper does all the messy math to work out how to divide
     * up the space within the current graphics window to neatly fit the board,
     * the cubes, and the word lists.
     */
    static void calculateGeometry(int rowCount, int columnCount) {
        double boardSize = min(gwp->getWidth() / 3 - 2 * INDENT,
                               gwp->getHeight() - 2 * LABEL_HEIGHT);
        gState.cubeSize = min((boardSize-BOARD_BORDER)/rowCount,
                              (boardSize-BOARD_BORDER)/columnCount);
        gState.board.w = gState.board.h = boardSize;
        gState.board.y = LABEL_HEIGHT + LABEL_HEIGHT;
        double leftover = gwp->getWidth() - gState.board.w - 2*INDENT;
        gState.scoreBox[HUMAN].x = INDENT;
        gState.scoreBox[HUMAN].y = gState.scoreBox[COMPUTER].y = gState.board.y;
        gState.scoreBox[HUMAN].h = gState.scoreBox[COMPUTER].h = LABEL_HEIGHT;
        gState.scoreBox[HUMAN].w = leftover*HUMAN_PERCENTAGE;
        gState.board.x = gState.scoreBox[HUMAN].x + gState.scoreBox[HUMAN].w + INDENT;
        gState.scoreBox[COMPUTER].x = gState.board.x + gState.board.w + INDENT;
        gState.scoreBox[COMPUTER].w = gwp->getWidth()
                                    - gState.scoreBox[COMPUTER].x - INDENT;
        gState.statusBox.x = INDENT;
        // gState.statusBox.y = gwp->getHeight() - 20;
        gState.statusBox.y = LABEL_HEIGHT;
        gState.statusBox.w = gwp->getWidth() - 2*INDENT;
        gState.statusBox.h = LABEL_HEIGHT;

        gState.rowCount = rowCount;
        gState.columnCount = columnCount;
        GLabel *lab = new GLabel("mmmmm");
        lab->setFont(WORD_FONT + "-" + integerToString(WORD_FONT_SIZE));
        gState.wordColumnWidth = lab->getWidth();
        for (gState.fontSize = 8; gState.fontSize < 48; gState.fontSize++) {
            GLabel *lab = new GLabel("M");
            lab->setFont(CUBE_FONT + "-" + integerToString(int(gState.fontSize)));
            if (lab->getWidth() > FONT_PERCENTAGE*gState.cubeSize) break;
        }
    }

    /*
     * Function: drawCenteredChar
     * --------------------------
     * Used to draw the letters in the center of the cube.
     * Note that this function centers the char both vertically and
     * horizontally around the point specified.
     */
    static void drawCenteredChar(double xc, double yc, char ch) {
        string s(1, ch);
        GLabel *lab = new GLabel(s);
        lab->setFont(CUBE_FONT + "-" + integerToString(int(gState.fontSize)));
        gwp->add(lab, xc - lab->getWidth()/2, yc + 0.4 * gState.fontSize);
    }

    static void drawAndFillRoundedRect(double x, double y, double width,
                                       double height, double r, string color) {
        gwp->setColor(color);
        fillRoundedRect(x, y,width, height, r, color);

        gwp->setColor("Black");
        drawRoundedRect(x, y, width, height, r);
    }

    /*
     * Draws one cube in its position, including the letter centered in the
     * middle of the cube.  If invert flag is true, reverse background and
     * letter colors.
     */
    static void drawCube(int row, int col, char ch, bool highlight) {
        drawAndFillRoundedRect(cubeX(col), cubeY(row),
                               gState.cubeSize, gState.cubeSize,
                               gState.cubeSize/5.0,
                               highlight ? DIE_COLOR_H : DIE_COLOR);
        gwp->setColor(highlight ? LETTER_COLOR_H : LETTER_COLOR);
        drawCenteredChar(cubeX(col) + gState.cubeSize/2.0,
                         cubeY(row) + gState.cubeSize/2.0, ch);
    }

    /*
     * Draws all of the cubes in position.  The cubes are drawn blank,
     * the client will fill in the letters by calling the exported function
     * function labelCube.
     */
    static void drawEmptyCubes() {
        for (int row = 0; row < gState.rowCount; row++) {
            for (int col = 0; col < gState.columnCount; col++) {
                drawCube(row, col, ' ', false);   // erase all cubes, start with blank chars
            }
        }
    }

    /*
     * Draws the specified score for the player according to player enum.
     */
    static void drawOneScore(Player player, int value) {
        string str = integerToString(value);
        GLabel **scoreLabel = player == COMPUTER ? &computerScoreLabel : &humanScoreLabel;
        *scoreLabel = new GLabel(str);
        (*scoreLabel)->setFont(SCORE_FONT + "-" + integerToString(SCORE_FONT_SIZE));
        (*scoreLabel)->setColor(LABEL_COLOR);
        int offset = player == COMPUTER ? 20 : 20;   // changed human offset from 0->20 (Marty)
        gwp->add(*scoreLabel, gState.scoreBox[player].x + gState.scoreBox[player].w - offset,
                 gState.scoreBox[player].y + LABEL_DY);
    }

    /*
     * Labels player word list with specified name and draws a line
     * underneath the label.  It also resets the player's score and
     * word list count back to zero.
     */
    static void drawPlayerLabel(Player player, string name) {
        gwp->setColor(LABEL_COLOR);
        gwp->drawLine(gState.scoreBox[player].x, gState.scoreBox[player].y,
                      gState.scoreBox[player].x + gState.scoreBox[player].w,
                      gState.scoreBox[player].y);
        GLabel *lab = new GLabel(name);
        lab->setFont(SCORE_FONT + "-" + integerToString(SCORE_FONT_SIZE));
        gwp->add(lab, gState.scoreBox[player].x, gState.scoreBox[player].y + LABEL_DY);
    }

    static void drawRoundedRect(double x, double y, double width, double height, double r) {
        gwp->drawLine(x + r, y, x + width - r, y);
        gwp->drawLine(x + r, y + height, x + width - r, y + height);
        gwp->drawLine(x, y + r, x, y + height - r);
        gwp->drawLine(x + width, y + r, x + width, y + height - r);

        GArc *arc = new GArc(2 * r, 2 * r, 90, 90);
        gwp->add(arc, x, y);
        arc = new GArc(2 * r, 2 * r, 180, 90);
        gwp->add(arc, x, y + height - 2 * r);
        arc = new GArc(2 * r, 2 * r, 270, 90);
        gwp->add(arc, x + width - 2 * r, y + height - 2 * r);
        arc = new GArc(2 * r, 2 * r, 0, 90);
        gwp->add(arc, x + width - 2 * r, y);
    }

    static void ensureInitialized() {
        if (!isInitialized()) {
            error("Boggle GUI has not been initialized yet");
        }
    }

    /*
     * I used to do this with SetEraseMode, but that left cruft behind, so instead
     * paint an opaque white box over the old score.
     */
    static void eraseOldScore(Player player) {
        GLabel **scoreLabel = player == COMPUTER ? &computerScoreLabel : &humanScoreLabel;
        gwp->remove(*scoreLabel);
    }

    /*
     * Shape-drawing functions
     * -----------------------
     * These routines use graphics library to draw rects, fill them in,
     * draw rounded corner rects and fill them in, too.
     *
     */
    static void fillBox(double x, double y, double width, double height, string color) {
        gwp->setColor(color);
        gwp->fillRect(x, y, width, height);
    }

    static void fillRoundedRect(double x, double y, double width, double height,
                                double r, string  color) {
        gwp->fillRect(x+r, y, width - 2 * r, height);
        gwp->fillRect(x, y+r, width, height - 2 * r);

        GArc *arc = new GArc(2 * r, 2 * r, 90, 90);
        arc->setFilled(true);
        arc->setColor(color);
        arc->setFillColor(color);
        gwp->add(arc, x, y);
        arc = new GArc(2 * r, 2 * r, 180, 90);
        arc->setFilled(true);
        arc->setColor(color);
        arc->setFillColor(color);
        gwp->add(arc, x, y + height - 2 * r);
        arc = new GArc(2 * r, 2 * r, 270, 90);
        arc->setFilled(true);
        arc->setColor(color);
        arc->setFillColor(color);
        gwp->add(arc, x + width - 2 * r, y + height - 2 * r);
        arc = new GArc(2 * r, 2 * r, 0, 90);
        arc->setFilled(true);
        arc->setColor(color);
         arc->setFillColor(color);
        gwp->add(arc, x + width - 2 * r, y);
    }
}
