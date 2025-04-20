#include "Knight.h"

// Constructor calls base class constructor
Knight::Knight(const std::string& color)
    : ChessPiece(color, 'N') {}

// Very basic example: pawn moves one step forward
bool Knight::isValidMove(int startRow, int startCol, int endRow, int endCol) const {
    
    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    
}