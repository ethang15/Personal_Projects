#pragma once
#include "ChessPiece.h"

class King : public ChessPiece {
public:
    // Constructor
    King(const std::string& color);

    // Override the pure virtual function
    bool isValidMove(int startRow, int startCol, int endRow, int endCol) const override;
};