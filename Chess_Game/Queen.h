#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece {
public:
    // Constructor
    Queen(const std::string& color);

    // Override the pure virtual function
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, bool isCapture) const override;
};