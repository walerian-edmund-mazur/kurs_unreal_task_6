/*****************************************************************************************
*Date: 2026-09-28
*File: GameBoard.h
*Description: GameBoard header file
******************************************************************************************/
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <string>
#include <vector>


class GameBoard {
public:
    explicit GameBoard(int size = 10);

    void initializeBoard();
    void printBoard();
    void updateBoard();
    void clearBoard();
    void randomizeBoard();
    void nextGeneration();
    bool isBoardEmpty();
    int getBoardSize();
    void setBoardSize(int size);
    void resizeBoard(int newSize);
    void saveBoardToFile(const std::string& filename);
    void loadBoardFromFile(const std::string& filename);
    void printBoardToFile(const std::string& filename);
    void loadBoardFromString(const std::string& boardData);
    std::string getBoardAsString();
    void printBoardToString(std::string& boardData);
    void loadBoardFromVector(const std::vector<std::vector<int>>& boardData);
    std::vector<std::vector<int>> getBoardAsVector();
    std::vector<std::vector<int>> board;

private:
    int boardSize;
};
#endif // GAMEBOARD_H