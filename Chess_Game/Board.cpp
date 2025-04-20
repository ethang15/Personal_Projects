#include "Board.h"
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

Board::Board() {
    // Initialize 8x8 grid with nullptr
    grid.resize(SIZE, std::vector<ChessPiece*>(SIZE, nullptr));
}

Board::~Board() {
    // Clean up dynamically allocated pieces
    for (auto& row : grid) {
        for (auto& piece : row) {
            delete piece;
            piece = nullptr;
        }
    }
}

void Board::placePiece(int row, int col, ChessPiece* piece) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        if (grid[row][col]) {
            delete grid[row][col];
        }
        grid[row][col] = piece;
    }
}

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol) {
    ChessPiece* piece = getPiece(startRow, startCol);
    if (piece && piece->isValidMove(startRow, startCol, endRow, endCol)) {
        delete grid[endRow][endCol];  // Remove captured piece if any
        grid[endRow][endCol] = piece;
        grid[startRow][startCol] = nullptr;
        return true;
    } else {
        std::cout << "Not a Valid Move, Try Again \n";
        return false;
    }
}

void Board::printBoard() const {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            ChessPiece* piece = grid[row][col];
            if (piece) {
                std::cout << piece->getSymbol();
            } else {
                std::cout << ".";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

ChessPiece* Board::getPiece(int row, int col) const {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
        return grid[row][col];
    }
    return nullptr;
}

void Board::initBoard() {
    // Black Pieces
    placePiece(0, 0, new Rook("black"));
    placePiece(0, 7, new Rook("black"));
    placePiece(0, 2, new Bishop("black"));
    placePiece(0, 5, new Bishop("black"));
    placePiece(0, 1, new Knight("black"));
    placePiece(0, 6, new Knight("black"));
    placePiece(0, 3, new Queen("black"));
    placePiece(0, 4, new King("black"));

    placePiece(1, 0, new Pawn("black"));
    placePiece(1, 1, new Pawn("black"));
    placePiece(1, 2, new Pawn("black"));
    placePiece(1, 3, new Pawn("black"));
    placePiece(1, 4, new Pawn("black"));
    placePiece(1, 5, new Pawn("black"));
    placePiece(1, 6, new Pawn("black"));
    placePiece(1, 7, new Pawn("black"));

    // White Pieces
    placePiece(7, 0, new Rook("white"));
    placePiece(7, 7, new Rook("white"));
    placePiece(7, 2, new Bishop("white"));
    placePiece(7, 5, new Bishop("white"));
    placePiece(7, 1, new Knight("white"));
    placePiece(7, 6, new Knight("white"));
    placePiece(7, 3, new Queen("white"));
    placePiece(7, 4, new King("white"));

    placePiece(6, 0, new Pawn("white"));
    placePiece(6, 1, new Pawn("white"));
    placePiece(6, 2, new Pawn("white"));
    placePiece(6, 3, new Pawn("white"));
    placePiece(6, 4, new Pawn("white"));
    placePiece(6, 5, new Pawn("white"));
    placePiece(6, 6, new Pawn("white"));
    placePiece(6, 7, new Pawn("white"));

}

bool Board::isPathClear(int startRow, int startCol, int endRow, int endCol) const {
    int rowStep = (endRow > startRow) ? 1 : (endRow < startRow) ? -1 : 0;
    int colStep = (endCol > startCol) ? 1 : (endCol < startCol) ? -1 : 0;
    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;

    while (currentRow != endRow || currentCol != endCol) {
        if (getPiece(currentRow, currentCol) != nullptr) {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }
    return true;
}

bool Board::isCapturingOwnPiece(int endRow, int endCol, const std::string& currentPlayer) const {
    ChessPiece* captured = getPiece(endRow, endCol);
    return captured != nullptr && captured->getColor() == currentPlayer;
}

bool Board::isWithinBounds(int row, int col) const {
    return (0 <= row && row < SIZE) && (0 <= col && col < SIZE);
}

bool Board::isKinginCheck(std::string& currentPlayer){
    int king_row = 0;
    int king_col = 0;
    char symbol = (currentPlayer == "white") ? 'K' : 'k';
    char enemy_queen = (currentPlayer == "white") ? 'q' : 'Q';
    char enemy_rook = (currentPlayer == "white") ? 'r' : 'R';
    char enemy_bishop = (currentPlayer == "white") ? 'b' : 'B';
    char enemy_knight = (currentPlayer == "white") ? 'n' : 'N';
    char enemy_pawn = (currentPlayer == "white") ? 'p' : 'P';
    std::vector<std::pair<int, int>> diagonals = { {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    std::vector<std::pair<int, int>> straights = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    std::vector<std::pair<int, int>> knights = {
        { -2, -1 }, { -2,  1 }, { -1, -2 }, { -1,  2 },
        {  1, -2 }, {  1,  2 }, {  2, -1 }, {  2,  1 }
    };

    findKing(currentPlayer, king_row, king_col);

    // Checking rows and columns
    for (const auto& dir : straights){
        int rowStep = dir.first;
        int colStep = dir.second;
        int currentRow = king_row + rowStep;
        int currentCol = king_col + colStep;
        while ((isWithinBounds(currentRow, currentCol))){
            ChessPiece* piece = grid[currentRow][currentCol];
            if (piece && ((piece->getSymbol() == enemy_queen) || (piece->getSymbol() == enemy_rook))) {
                return true;
            }
            currentRow += rowStep;
            currentCol += colStep;
        }
    }

    // Checking diagonals
    for (const auto& dir : diagonals){
        int rowStep = dir.first;
        int colStep = dir.second;
        int currentRow = king_row + rowStep;
        int currentCol = king_col + colStep;
        while ((isWithinBounds(currentRow, currentCol))){
            ChessPiece* piece = grid[currentRow][currentCol];
            if (piece && ((piece->getSymbol() == enemy_queen) || (piece->getSymbol() == enemy_bishop))) {
                return true;
            }
            currentRow += rowStep;
            currentCol += colStep;
        }
    }

    // Checking Knight moves
    for (const auto& dir : knights){
        int rowStep = dir.first;
        int colStep = dir.second;
        int currentRow = king_row + rowStep;
        int currentCol = king_col + colStep;

        if ((isWithinBounds(currentRow, currentCol))){
            ChessPiece* piece = grid[currentRow][currentCol];
            if (piece && (piece->getSymbol() == enemy_knight)) {
                return true;
            }
        }
        currentRow = king_row;
        currentCol = king_col;
    }
    
    return false;
}

void Board::findKing(std::string& currentPlayer, int& row, int& col){
    char symbol = (currentPlayer == "white") ? 'K' : 'k';

    for (int i = 0; i < SIZE; ++i){
        for (int k = 0; k < SIZE; ++k){
            ChessPiece* piece = grid[i][k];
            if (piece && piece->getSymbol() == symbol) {
                row = i;
                col = k;
                return;
            }
        }
    }
}