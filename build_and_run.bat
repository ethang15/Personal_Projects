@echo off
echo Compiling...

g++ main.cpp Board.cpp ChessPiece.cpp Pawn.cpp Rook.cpp Knight.cpp Bishop.cpp Queen.cpp King.cpp Game.cpp -o main.exe

if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b
)

echo Running program...
main.exe