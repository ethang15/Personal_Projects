#include "Game.h"

// Constructor
Game::Game() {
    board.initBoard();
    currentPlayer = "white";
    gameover = false;
    command = "";
    validmove = false;
}

// Main game loop
void Game::run() {
    while(!gameover){
        validmove = false;
        board.printBoard();
        std::cout << currentPlayer << "'s Turn" << std::endl;
        std::getline(std::cin, command);
        if (command != "quit"){
            validmove = parseAndExecuteMove(command, currentPlayer);
            if (validmove) {
                switchPlayer();
            }
        }
        else{
            gameover = true;
        }
    }
}

// Toggle current player
void Game::switchPlayer() {
    currentPlayer = (currentPlayer == "white") ? "black" : "white";
}

// Parse move command and attempt to execute it
bool Game::parseAndExecuteMove(const std::string& input, std::string& currentPlayer) {
    
    if (input.length() != 4){
        std::cout << "Not a Valid Move, Try Again \n";
        return false;
    }
    
    std::string from = input.substr(0,2);
    std::string to = input.substr(2,2);

    int startCol = from[0] - 'a';       
    int startRow = 8 - (from[1] - '0');   

    int endCol = to[0] - 'a';
    int endRow = 8 - (to[1] - '0');

    ChessPiece* pieceToMove = board.getPiece(startRow, startCol);
    ChessPiece* endPiece = board.getPiece(endRow, endCol);

    std::string opponentColor = (currentPlayer == "white") ? "black" : "white";

    bool isCapturing = (endPiece && pieceToMove->getColor() != endPiece->getColor());

    bool inBoundsStart = board.isWithinBounds(startRow, startCol);
    bool inBoundsEnd = board.isWithinBounds(endRow, endCol);
    bool pathClear = board.isPathClear(startRow, startCol, endRow, endCol);
    bool notCapturingOwn = !board.isCapturingOwnPiece(endRow, endCol, currentPlayer);
    bool doesNotExposeKing = !board.doesMoveExposeKing(startRow, startCol, endRow, endCol, currentPlayer);
    bool pieceHasValidMove = pieceToMove->isValidMove(startRow, startCol, endRow, endCol, isCapturing);

    if (pieceToMove && inBoundsStart && inBoundsEnd && pathClear && notCapturingOwn && doesNotExposeKing && pieceHasValidMove) {

        std::cout << "Valid Move" << std::endl;
        bool moveAllowed = board.movePiece(startRow, startCol, endRow, endCol, isCapturing);
        
        board.pawnPromotion(endRow, endCol, currentPlayer, pieceToMove);
        
        bool isCheck = board.isKingInCheck(opponentColor);
        if(isCheck){
            std::cout << opponentColor << " Is in Check" << std::endl;
        }
        
        return moveAllowed;
    }
    else{

        // Individual checks with if statements and custom error messages
        if (!inBoundsStart) {
            std::cout << "Starting position is out of bounds" << std::endl;
        }
        if (!inBoundsEnd) {
            std::cout << "Ending position is out of bounds" << std::endl;
        }
        if (!pathClear) {
            std::cout << "Path is not clear" << std::endl;
        }
        if (!notCapturingOwn) {
            std::cout << "Cannot capture your own piece" << std::endl;
        }
        if (!doesNotExposeKing) {
            std::cout << "Move would expose your king" << std::endl;
        }
        if (!pieceHasValidMove) {
            std::cout << "Piece move is invalid" << std::endl;
        }

        return false;
    }

}
