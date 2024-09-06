#ifndef SUDOKU_BOARD_HPP
#define SUDOKU_BOARD_HPP

#include <iostream>
#include <vector>
#include "generator.hpp"

typedef std::pair<int, int> Cell;
class SudokuBoard{

    public:

        SudokuBoard(std::vector<std::vector<int>> board);
        std::vector<int>& operator[](int);
        void printBoard() const;
        bool isBoardFull();
        bool isCellSafe(int row, int col, int num);
        
        Generator<std::pair<Cell, int>> getBoardIterator();
        Generator<std::pair<Cell, int>> getCellInfluenceIterator(int row, int col);
        const int N;
    
    private:
        std::vector<std::vector<int>> m_board;

};

#endif