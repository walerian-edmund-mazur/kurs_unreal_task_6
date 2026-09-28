/*****************************************************************************************
*Date: 2026-09-28
*File: GameBoard.cpp
*Description: GameBoard def file
******************************************************************************************/
#include "GameBoard.h"
#include "Bacteria.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

GameBoard::GameBoard(int size) : boardSize(size) {
	if (size <= 0) {
		throw std::invalid_argument("Board size must be greater than zero");
	}
}

void GameBoard::initializeBoard() {
	board.assign(boardSize, std::vector<int>(boardSize, 0));
}

void GameBoard::printBoard() {
	std::cout << '+' << std::string(board.size() * 2, '-') << "+\n";
	for (const std::vector<int>& row : board) {
		std::cout << '|';
		for (int cell : row) {
			std::cout << (cell != 0 ? "[]" : "  ");
		}
		std::cout << "|\n";
	}
	std::cout << '+' << std::string(board.size() * 2, '-') << "+\n";
}

void GameBoard::updateBoard() {
	nextGeneration();
}

void GameBoard::clearBoard() {
	for (std::vector<int>& row : board) {
		std::fill(row.begin(), row.end(), 0);
	}
}

void GameBoard::randomizeBoard() {
	if (board.empty()) {
		initializeBoard();
	}

	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::bernoulli_distribution cellState(0.5);

	for (std::vector<int>& row : board) {
		for (int& cell : row) {
			cell = cellState(generator) ? 1 : 0;
		}
	}
}

void GameBoard::nextGeneration() {
	if (board.empty()) {
		return;
	}

	std::vector<std::vector<int>> nextBoard(board.size(), std::vector<int>(board.size(), 0));

	for (std::size_t row = 0; row < board.size(); ++row) {
		for (std::size_t column = 0; column < board[row].size(); ++column) {
			int liveNeighbors = 0;

			for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
				for (int columnOffset = -1; columnOffset <= 1; ++columnOffset) {
					if (rowOffset == 0 && columnOffset == 0) {
						continue;
					}

					const int neighborRow = static_cast<int>(row) + rowOffset;
					const int neighborColumn = static_cast<int>(column) + columnOffset;

					if (neighborRow >= 0 && neighborRow < static_cast<int>(board.size()) &&
						neighborColumn >= 0 && neighborColumn < static_cast<int>(board[row].size())) {
						liveNeighbors += board[neighborRow][neighborColumn] != 0;
					}
				}
			}

			Bacteria cell(board[row][column] != 0);
			cell.update(liveNeighbors);
			nextBoard[row][column] = cell.isAlive() ? 1 : 0;
		}
	}

	board = nextBoard;
}

bool GameBoard::isBoardEmpty() {
	for (const std::vector<int>& row : board) {
		for (int cell : row) {
			if (cell != 0) {
				return false;
			}
		}
	}

	return true;
}

int GameBoard::getBoardSize() {
	return boardSize;
}

void GameBoard::setBoardSize(int size) {
	if (size <= 0) {
		throw std::invalid_argument("Board size must be greater than zero");
	}

	boardSize = size;
}

void GameBoard::resizeBoard(int newSize) {
	if (newSize <= 0) {
		throw std::invalid_argument("Board size must be greater than zero");
	}

	board.resize(newSize);
	for (std::vector<int>& row : board) {
		row.resize(newSize, 0);
	}
	boardSize = newSize;
}

void GameBoard::saveBoardToFile(const std::string& filename) {
	std::ofstream outputFile(filename);
	if (!outputFile) {
		throw std::runtime_error("Could not open file for writing: " + filename);
	}

	outputFile << getBoardAsString();
}

void GameBoard::loadBoardFromFile(const std::string& filename) {
	std::ifstream inputFile(filename);
	if (!inputFile) {
		throw std::runtime_error("Could not open file for reading: " + filename);
	}

	std::ostringstream boardData;
	boardData << inputFile.rdbuf();
	loadBoardFromString(boardData.str());
}

void GameBoard::printBoardToFile(const std::string& filename) {
	std::ofstream outputFile(filename);
	if (!outputFile) {
		throw std::runtime_error("Could not open file for writing: " + filename);
	}

	for (const std::vector<int>& row : board) {
		for (int cell : row) {
			outputFile << cell << ' ';
		}
		outputFile << '\n';
	}
}

void GameBoard::loadBoardFromString(const std::string& boardData) {
	std::istringstream input(boardData);
	int size = 0;
	if (!(input >> size) || size <= 0) {
		throw std::invalid_argument("Board data must start with a positive board size");
	}

	std::vector<std::vector<int>> loadedBoard(size, std::vector<int>(size));
	for (std::vector<int>& row : loadedBoard) {
		for (int& cell : row) {
			if (!(input >> cell)) {
				throw std::invalid_argument("Board data does not contain enough cells");
			}
			cell = cell != 0 ? 1 : 0;
		}
	}

	boardSize = size;
	board = loadedBoard;
}

std::string GameBoard::getBoardAsString() {
	std::ostringstream output;
	output << boardSize << '\n';

	for (const std::vector<int>& row : board) {
		for (int cell : row) {
			output << cell << ' ';
		}
		output << '\n';
	}

	return output.str();
}

void GameBoard::printBoardToString(std::string& boardData) {
	boardData = getBoardAsString();
}

void GameBoard::loadBoardFromVector(const std::vector<std::vector<int>>& boardData) {
	if (boardData.empty() || boardData.size() != boardData.front().size()) {
		throw std::invalid_argument("Board data must be a non-empty square matrix");
	}

	for (const std::vector<int>& row : boardData) {
		if (row.size() != boardData.size()) {
			throw std::invalid_argument("Board data must be a square matrix");
		}
	}

	board = boardData;
	boardSize = static_cast<int>(board.size());
	for (std::vector<int>& row : board) {
		for (int& cell : row) {
			cell = cell != 0 ? 1 : 0;
		}
	}
}

std::vector<std::vector<int>> GameBoard::getBoardAsVector() {
	return board;
}