#include "Pawn.h"

// Constructor calls base class constructor
Pawn::Pawn(const std::string& color)
    : ChessPiece(color, 'P') {}

bool Pawn::isValidMove(int startRow, int startCol, int endRow, int endCol, bool IsCapture) const {
    int direction = (color == "white") ? -1 : 1;
    int initRow = (color == "white") ? 6 : 1;

    if(IsCapture) {
        if ((startCol == endCol + 1 || startCol == endCol - 1) && endRow == startRow + direction){
            return true;
        }
    }
    else{
        if (startCol == endCol && endRow == startRow + direction) {
            return true;
        }

        if (startRow == initRow && endRow-startRow == 2*direction) {
            return true;
        }
    }
    

    return false;
}