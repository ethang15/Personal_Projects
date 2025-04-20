#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
    // Constructor
    Pawn(const std::string& color);

    // Override the pure virtual function
    bool isValidMove(int startRow, int startCol, int endRow, int endCol) const override;
};