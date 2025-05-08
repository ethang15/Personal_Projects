#pragma once
#include <string>

class ChessPiece {
protected:
    std::string color;
    char symbol;

public:
    ChessPiece(const std::string& color, char symbol);
    virtual ~ChessPiece();

    std::string getColor() const;
    char getSymbol() const;

    virtual bool isValidMove(int startRow, int startCol, int endRow, int endCol, bool isCapture) const = 0;
};