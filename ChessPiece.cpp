#include "ChessPiece.h"

// Constructor
ChessPiece::ChessPiece(const std::string& color, char symbol)
    : color(color), symbol(symbol) {}

// Virtual destructor
ChessPiece::~ChessPiece() {}

// Getter for color
std::string ChessPiece::getColor() const {
    return color;
}

// Getter for symbol
char ChessPiece::getSymbol() const {
    return (color == "white") ? symbol : std::tolower(symbol);
}