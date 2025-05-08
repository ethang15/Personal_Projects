#include "Rook.h"

// Constructor calls base class constructor
Rook::Rook(const std::string& color)
    : ChessPiece(color, 'R') {}

// Very basic example: pawn moves one step forward
bool Rook::isValidMove(int startRow, int startCol, int endRow, int endCol, bool isCapture) const {
    
    return (startRow != endRow || startCol != endCol) &&
       (startRow == endRow || startCol == endCol);
       
}