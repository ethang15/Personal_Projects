#include "Pawn.h"

// Constructor calls base class constructor
Pawn::Pawn(const std::string& color)
    : ChessPiece(color, 'P') {}

// Very basic example: pawn moves one step forward
bool Pawn::isValidMove(int startRow, int startCol, int endRow, int endCol) const {
    int direction = (color == "white") ? -1 : 1;

    // Basic forward move by 1 square
    if (startCol == endCol && endRow == startRow + direction) {
        return true;
    }

    // Could add double move, capturing, en passant, promotion, etc.
    return false;
}