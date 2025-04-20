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

    if (pieceToMove->isValidMove(startRow, startCol, endRow, endCol) && board.isWithinBounds(startRow,startCol) && 
    board.isWithinBounds(endRow, endCol) && board.isPathClear(startRow, startCol, endRow, endCol) && 
    !board.isCapturingOwnPiece(endRow, endCol, currentPlayer) && !board.doesMoveExposeKing(startRow, startCol, endRow, endCol, currentPlayer)) {


        std::cout << "Valid Move \n";
        bool moveAllowed = board.movePiece(startRow, startCol, endRow, endCol);
        if ((pieceToMove->getSymbol() == 'P' && endRow == 0) || (pieceToMove->getSymbol() == 'p' && endRow == 7)){
            board.pawnPromotion(endRow, endCol, currentPlayer);
        }
        
        return moveAllowed;
    }
    else{
        bool pieceHasValidMove = pieceToMove && pieceToMove->isValidMove(startRow, startCol, endRow, endCol);
        bool inBoundsStart = board.isWithinBounds(startRow, startCol);
        bool inBoundsEnd = board.isWithinBounds(endRow, endCol);
        bool pathClear = board.isPathClear(startRow, startCol, endRow, endCol);
        bool notCapturingOwn = !board.isCapturingOwnPiece(endRow, endCol, currentPlayer);
        bool exposesKing = !board.doesMoveExposeKing(startRow, startCol, endRow, endCol, currentPlayer);
        
        std::cout << "Piece has valid move: " << (pieceHasValidMove ? "true" : "false") << std::endl;
        std::cout << "Start in bounds: " << (inBoundsStart ? "true" : "false") << std::endl;
        std::cout << "End in bounds: " << (inBoundsEnd ? "true" : "false") << std::endl;
        std::cout << "Path is clear: " << (pathClear ? "true" : "false") << std::endl;
        std::cout << "Not capturing own piece: " << (notCapturingOwn ? "true" : "false") << std::endl;
        std::cout << "Move exposes king: " << (exposesKing ? "true" : "false") << std::endl;

        bool moveIsValid = inBoundsStart && inBoundsEnd && pathClear && notCapturingOwn && !exposesKing;
        std::cout << "Overall move is valid: " << (moveIsValid ? "true" : "false") << std::endl;
        std::cout << "Not a Valid Move, Try Again \n";
        return false;
    }

}
