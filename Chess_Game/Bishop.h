#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece {
public:
    // Constructor
    Bishop(const std::string& color);

    // Override the pure virtual function
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, bool isCapture) const override;
};