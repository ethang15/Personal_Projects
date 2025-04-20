#pragma once
#include "Board.h"

class Game {
public:
    Game();
    void run();  // main game loop

private:
    Board board;
    std::string currentPlayer;
    std::string command;
    bool gameover;
    bool validmove;


    bool parseAndExecuteMove(const std::string& input, std::string& currentPlayer);
    void switchPlayer();
};