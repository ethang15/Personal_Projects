#include "King.h"

// Constructor calls base class constructor
King::King(const std::string& color)
    : ChessPiece(color, 'K') {}

// Very basic example: pawn moves one step forward
bool King::isValidMove(int startRow, int startCol, int endRow, int endCol) const {

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    return (!(rowDiff == 0 && colDiff == 0) && (rowDiff <= 1 && colDiff <= 1));
       
}