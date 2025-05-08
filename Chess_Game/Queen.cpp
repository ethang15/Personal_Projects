#include "Queen.h"

// Constructor calls base class constructor
Queen::Queen(const std::string& color)
    : ChessPiece(color, 'Q') {}

// Very basic example: pawn moves one step forward
bool Queen::isValidMove(int startRow, int startCol, int endRow, int endCol, bool isCapture) const {

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    return ((rowDiff != 0 && colDiff != 0) && (rowDiff == colDiff)) || 
    ((startRow != endRow || startCol != endCol) && (startRow == endRow || startCol == endCol));
       
}