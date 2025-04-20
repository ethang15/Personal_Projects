#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece {
public:
    // Constructor
    Rook(const std::string& color);

    // Override the pure virtual function
    bool isValidMove(int startRow, int startCol, int endRow, int endCol) const override;
};