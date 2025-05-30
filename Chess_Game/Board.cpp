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

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol, bool isCapturing) {
    ChessPiece* piece = getPiece(startRow, startCol);
    if (piece && piece->isValidMove(startRow, startCol, endRow, endCol, isCapturing)) {
        delete grid[endRow][endCol];  // Remove captured piece if any
        grid[endRow][endCol] = piece;
        grid[startRow][startCol] = nullptr;
        return true;
    } else {
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
    ChessPiece* piece = grid[startRow][startCol];
    if (!piece) return false;

    // Knights can jump, so path clearance doesn't apply
    if (piece->getSymbol() == 'N' || piece->getSymbol() == 'n') {
        return true;
    }    
    
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

bool Board::isKingInCheck(std::string& currentPlayer) {
    int king_row = 0, king_col = 0;
    
    findKing(currentPlayer, king_row, king_col);
    return isSquareAttacked(king_row, king_col, currentPlayer);
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

bool Board::doesMoveExposeKing(int startRow, int startCol, int endRow, int endCol, std::string& currentPlayer) {
    ChessPiece* movedPiece = grid[startRow][startCol];
    ChessPiece* capturedPiece = grid[endRow][endCol];

    // Simulate the move
    grid[endRow][endCol] = movedPiece;
    grid[startRow][startCol] = nullptr;

    bool kingInCheck = isKingInCheck(currentPlayer);

    // Undo the move
    grid[startRow][startCol] = movedPiece;
    grid[endRow][endCol] = capturedPiece;

    return kingInCheck;
}

void Board::pawnPromotion(int endRow, int endCol, std::string& currentPlayer, ChessPiece* pieceToMove) {
    if ((pieceToMove->getSymbol() == 'P' && endRow == 0) || (pieceToMove->getSymbol() == 'p' && endRow == 7)){
        auto promotedQueen = (currentPlayer == "white") 
        ? new Queen("white") 
        : new Queen("black");

        placePiece(endRow, endCol, promotedQueen);
    }
}

bool Board::isCheckMate(std::string& currentPlayer){
    int king_row = 0, king_col = 0;
    
    findKing(currentPlayer, king_row, king_col);

    // Can the King Move to Safety?
    for(int i = king_row - 1; i < king_row + 2; i++){
        for(int k = king_col - 1; k < king_col + 2; k++){
            if(isWithinBounds(i,k)){
                if(!isSquareAttacked(i,k,currentPlayer)){
                    return false;
                }
            }
        }
    }

    // Can the King be Protected by Another Piece?
    // Position and Piece Attacking?
    // Pieces that can block (use isSquareAttacked but backwards)
    
    
    return true;
}

bool Board::isSquareAttacked(int row, int col, std::string& currentPlayer) {
    std::string opponentColor = (currentPlayer == "white") ? "black" : "white";

    char enemy_queen  = (opponentColor == "white") ? 'Q' : 'q';
    char enemy_rook   = (opponentColor == "white") ? 'R' : 'r';
    char enemy_bishop = (opponentColor == "white") ? 'B' : 'b';
    char enemy_knight = (opponentColor == "white") ? 'N' : 'n';
    char enemy_pawn   = (opponentColor == "white") ? 'P' : 'p';

    std::vector<std::pair<int, int>> diagonals = { {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };
    std::vector<std::pair<int, int>> straights = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    std::vector<std::pair<int, int>> knights = {
        { -2, -1 }, { -2,  1 }, { -1, -2 }, { -1,  2 },
        {  1, -2 }, {  1,  2 }, {  2, -1 }, {  2,  1 }
    };

    auto pawns = (opponentColor == "white")
        ? std::vector<std::pair<int, int>>{ {-1, -1}, {-1, 1} } // white pawns attack upward
        : std::vector<std::pair<int, int>>{ {1, -1}, {1, 1} };  // black pawns attack downward

    // Straights: Rooks + Queens
    for (const auto& [rowStep, colStep] : straights) {
        int r = row + rowStep;
        int c = col + colStep;
        while (isWithinBounds(r, c)) {
            ChessPiece* piece = grid[r][c];
            if (piece) {
                if (piece->getSymbol() == enemy_rook || piece->getSymbol() == enemy_queen)
                    return true;
                break;
            }
            r += rowStep;
            c += colStep;
        }
    }

    // Diagonals: Bishops + Queens
    for (const auto& [rowStep, colStep] : diagonals) {
        int r = row + rowStep;
        int c = col + colStep;
        while (isWithinBounds(r, c)) {
            ChessPiece* piece = grid[r][c];
            if (piece) {
                if (piece->getSymbol() == enemy_bishop || piece->getSymbol() == enemy_queen)
                    return true;
                break;
            }
            r += rowStep;
            c += colStep;
        }
    }

    // Knights
    for (const auto& [rowStep, colStep] : knights) {
        int r = row + rowStep;
        int c = col + colStep;
        if (isWithinBounds(r, c)) {
            ChessPiece* piece = grid[r][c];
            if (piece && piece->getSymbol() == enemy_knight)
                return true;
        }
    }

    // Pawns
    for (const auto& [rowStep, colStep] : pawns) {
        int r = row + rowStep;
        int c = col + colStep;
        if (isWithinBounds(r, c)) {
            ChessPiece* piece = grid[r][c];
            if (piece && piece->getSymbol() == enemy_pawn)
                return true;
        }
    }

    return false;
}
