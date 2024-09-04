#include <iostream>
#include <vector>
#include <map>
#include "sudoku_board.hpp"

#define N 9 // Size of the Sudoku grid (9x9)

bool areAllMapsEmpty(std::map<int, std::map<int, std::vector<int>>>& outerMap) {
        for (const auto& outerPair : outerMap) {
            const std::map<int, std::vector<int>>& innerMap = outerPair.second;
            for (const auto& innerPair : innerMap) {
                const std::vector<int> constraint = innerPair.second;
                if (!constraint.empty()) {
                    return false;  // Found a non-empty map
                }
            }
        }
    return true;  // All maps are empty
}

bool solveSudokuHuman(SudokuBoard board) {

    // std::map<int, std::map<int, std::vector<int>>> constraints = createConstraints(board);

    bool step = true;

    //while (!areAllMapsEmpty(constraints) && step){
      //  step = nakedSingles(board, constraints);
        //printBoard(board);
        //std::cout << std::endl;
    //}

    std::cout << std::endl;

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

    SudokuBoard m_board{board};

    if (solveSudokuHuman(m_board)) {
        std::cout << "Sudoku solved successfully:\n";
        m_board.printBoard();
    } else {
        std::cout << "No solution exists.\n";
        m_board.printBoard();
    }

    return 0;
}
