#ifndef SUDOKU_BOARD_HPP
#define SUDOKU_BOARD_HPP

#include <iostream>
#include <vector>

class SudokuBoard{

    public:

        SudokuBoard(std::vector<std::vector<int>> board);
        std::vector<int>& operator[](int);
        void printBoard() const;
        bool isSafe(int row, int col, int num);
        
        std::vector<int> getCellInfluenceIterator(int row, int col);
    
    private:
        std::vector<std::vector<int>> m_board;

};

#endif