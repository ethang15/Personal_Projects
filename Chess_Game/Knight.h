#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece {
public:
    // Constructor
    Knight(const std::string& color);

    // Override the pure virtual function
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, bool isCapture) const override;
};