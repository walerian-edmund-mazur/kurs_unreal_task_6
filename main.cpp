/*****************************************************************************************
*Date: 2026-09-28
*Task: Life Game in cpp
*Author: Walerian
******************************************************************************************/
#include "GameBoard.h"

#include <chrono>
#include <iostream>
#include <thread>

int main() {
    constexpr int boardSize = 10;
    constexpr int maximumGenerations = 50;
    constexpr int millisecondsBetweenGenerations = 400;

    GameBoard gameBoard(boardSize);
    gameBoard.initializeBoard();
    gameBoard.randomizeBoard();

    std::cout << "Welcome to the Life Game!\n";
    std::cout << "Starting with a randomized " << boardSize << "x" << boardSize << " board.\n";

    for (int generation = 0; generation < maximumGenerations; ++generation) {
        std::cout << "\x1B[2J\x1B[H";
        std::cout << "Life Game - randomized input\n";
        std::cout << "Generation: " << generation << "\n\n";
        gameBoard.printBoard();

        if (gameBoard.isBoardEmpty()) {
            std::cout << "\nAll bacteria have died.\n";
            break;
        }

        const std::vector<std::vector<int>> previousBoard = gameBoard.getBoardAsVector();
        gameBoard.updateBoard();

        if (gameBoard.getBoardAsVector() == previousBoard) {
            std::cout << "\nThe board has stabilized.\n";
            break;
        }

        std::cout.flush();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(millisecondsBetweenGenerations));
    }

    std::cout << "\nGame over. Press Enter to close.\n";
    std::cin.get();

    return 0;
}