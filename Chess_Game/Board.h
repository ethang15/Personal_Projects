#pragma once
#include "ChessPiece.h"
#include <vector>
#include <memory>  // For smart pointers
#include <iostream>

class Board {
private:
    static const int SIZE = 8;

    // 2D board of ChessPiece pointers
    std::vector<std::vector<ChessPiece*>> grid;

public:
    Board();
    ~Board();

    void placePiece(int row, int col, ChessPiece* piece);
    bool movePiece(int startRow, int startCol, int endRow, int endCol);
    void printBoard() const;
    ChessPiece* getPiece(int row, int col) const;
    void initBoard();
    bool isPathClear(int startRow, int startCol, int endRow, int endCol) const;
    bool isCapturingOwnPiece(int endRow, int endCol, const std::string& currentPlayer) const;
    bool isWithinBounds(int row, int col) const;
    bool isKingInCheck(std::string& currentPlayer);
    void findKing(std::string& currentPlayer, int& row, int& col);
    bool doesMoveExposeKing(int startRow, int startCol, int endRow, int endCol, std::string& currentPlayer);
};