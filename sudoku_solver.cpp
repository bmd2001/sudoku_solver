#include <iostream>
#include <vector>
#include <map>
#include "sudoku_board.hpp"
#include "naked_singles.hpp"

#define N 9 // Size of the Sudoku grid (9x9)

bool solveSudokuHuman(SudokuBoard& board) {

    Constraints constraints{board};

    bool step = true;
    while (!board.isBoardFull() && step){
        step = nakedSingles(board, constraints);
        board.printBoard();
    }

    return step;
}

int main() {
    // Example Sudoku puzzle (0 represents an empty cell)
    std::vector<std::vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    std::vector<std::vector<int>> board2 = {
        {5, 0, 6, 8, 0, 4, 0, 0, 0},
        {0, 0, 2, 0, 0, 5, 0, 0, 8},
        {0, 0, 0, 0, 6, 9, 5, 2, 0},
        {0, 0, 7, 0, 0, 0, 0, 3, 0},
        {0, 0, 4, 0, 8, 0, 6, 0, 0},
        {0, 8, 0, 0, 0, 0, 4, 0, 0},
        {0, 0, 0, 5, 9, 0, 0, 0, 6},
        {9, 0, 0, 4, 0, 0, 7, 0, 0},
        {0, 0, 5, 0, 3, 0, 8, 0, 2}
    };


    SudokuBoard m_board{board};
    std::cout << "First Sudoku Board:\n";
    m_board.printBoard();

    if (solveSudokuHuman(m_board)) {
        std::cout << "Sudoku solved successfully:\n";
        m_board.printBoard();
    } else {
        std::cout << "No solution exists.\n";
        m_board.printBoard();
    }

    SudokuBoard m_board2{board2};
    std::cout << "Second Sudoku Board:\n";
    m_board2.printBoard();
    if (solveSudokuHuman(m_board2)) {
        std::cout << "Sudoku solved successfully:\n";
        m_board2.printBoard();
    } else {
        std::cout << "No solution exists.\n";
        m_board2.printBoard();
    }

    return 0;
}
