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
    std::string from = input.substr(0,2);
    std::string to = input.substr(2,2);

    int startCol = from[0] - 'a';       
    int startRow = 8 - (from[1] - '0');   

    int endCol = to[0] - 'a';
    int endRow = 8 - (to[1] - '0');

    if (board.isWithinBounds(startRow,startCol) && board.isWithinBounds(endRow, endCol) && 
    board.isPathClear(startRow, startCol, endRow, endCol) && !board.isCapturingOwnPiece(endRow, endCol, currentPlayer)) {

        return board.movePiece(startRow, startCol, endRow, endCol);
    }
    else{
        std::cout << "Not a Valid Move, Try Again \n";
        return false;
    }

}
