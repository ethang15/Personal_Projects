#include "Bishop.h"

// Constructor calls base class constructor
Bishop::Bishop(const std::string& color)
    : ChessPiece(color, 'B') {}

// Very basic example: pawn moves one step forward
bool Bishop::isValidMove(int startRow, int startCol, int endRow, int endCol) const {
    
    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);
    return (rowDiff != 0 && colDiff != 0) && (rowDiff == colDiff);

}