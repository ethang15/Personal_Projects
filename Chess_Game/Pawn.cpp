#include "Pawn.h"

// Constructor calls base class constructor
Pawn::Pawn(const std::string& color)
    : ChessPiece(color, 'P') {}

bool Pawn::isValidMove(int startRow, int startCol, int endRow, int endCol) const {
    int direction = (color == "white") ? -1 : 1;
    int initRow = (color == "white") ? 6 : 1;

    // Basic forward move by 1 square
    if (startCol == endCol && endRow == startRow + direction) {
        return true;
    }

    if (startRow == initRow && endRow-startRow == 2*direction) {
        return true;
    }

    return false;
}