#include "Piezas.h"
#include <vector>
#include <iostream>
using namespace std;

/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas() {
    board.clear();
    board.resize(BOARD_ROWS, std::vector<Piece>(BOARD_COLS));
    for(int i=0; i<(int)board.size(); i++) {
        for(int j=0; j<(int)board[i].size(); j++) {
            board[i][j] = Blank;
        }
    }
    turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset() {
    for(int i=0; i<(int)board.size(); i++) {
        for(int j=0; j<(int)board[i].size(); j++) {
            board[i][j] = Blank;
        }
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    int taken=0;
    Piece currentPiece = turn;
    
    if(column >= BOARD_COLS) {
        if(turn == X) turn = O;
        else turn = X;
        return Invalid;
    }
    
    for(int row=0; row<(int)board.size(); row++) {
        if(board[row][column] == X) taken++;
        else if(board[row][column] == O) taken++;
        else {
            board[row][column] = turn;
            if(turn == X) turn = O;
            else turn = X;
            return currentPiece;
        }
    }
    if(taken == BOARD_ROWS-1) {
        if(turn == X) turn = O;
        else turn = X;
        return Blank;
    }
        
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if (row >= BOARD_ROWS) return Invalid;
    else if (column >= BOARD_COLS) return Invalid;
    else if(board[row][column] == Blank) return Blank;
    else return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    bool xWin = false;
    bool oWin = false;
    //Check for full board
    for(int i=0; i<(int)board.size(); i++) {
        for(int j=0; j<(int)board[i].size(); j++) {
            if(board[i][j] == Blank)
                return Invalid;
        }
    }

    
    //Board is full - find winner
    //Check horizontal winner
    for(int row=0; row<BOARD_ROWS; row++) {
        int xCount = 0;
        int oCount = 0;
        for(int column=0; column<BOARD_COLS; column++) {
            if(pieceAt(row, column) == X) xCount++;
            else oCount++;
        }
        if(xCount==BOARD_COLS) xWin = true;
        else if(oCount==BOARD_COLS) oWin = true;
    }
    //Checking for vertical winner
    for(int column=0; column<BOARD_COLS; column++) {
        int xCount = 0;
        int oCount = 0;
        for(int row=0; row<BOARD_ROWS; row++) {
            if(pieceAt(row, column) == X) xCount++;
            else oCount++;
        }
        if(xCount==BOARD_ROWS) xWin = true;
        else if(oCount==BOARD_ROWS) oWin = true;
    }
    if(xWin == true && oWin == true) return Blank;
    else if (xWin == true) return X;
    else if (oWin == true) return O;
    else return Blank;
}

