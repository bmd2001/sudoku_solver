#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include "sudoku_board.hpp"
#include "naked_singles.hpp"
#include "hidden_singles.hpp"
#include "naked_groups.hpp"

#define N 9 // Size of the Sudoku grid (9x9)

bool solveSudokuHuman(SudokuBoard& board) {
    auto start = std::chrono::high_resolution_clock::now();

    Constraints constraints{board};
    std::vector<std::unique_ptr<SudokuStrategy>> strategies;
    strategies.push_back(std::make_unique<NakedSingles>());
    strategies.push_back(std::make_unique<HiddenSingles>());
    strategies.push_back(std::make_unique<NakedGroups>());

    while (!board.isBoardFull()){
        bool progressMade = false;

        for (const auto& strategy : strategies){
            progressMade = strategy->apply(board, constraints);  // Apply strategy
            strategy->print();  // Print results regardless of success

            if (progressMade) {
                break;  // Stop trying other strategies and go for another iteration
            }
        }

        // If no strategy made progress, exit the loop
        if (!progressMade) {
            break;
        }

        if (!board.isBoardFull()){
            board.printBoard();
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

    return board.isBoardFull();
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
        {0, 0, 0, 0, 0, 4, 0, 2, 8},
        {4, 0, 6, 0, 0, 0, 0, 0, 5},
        {1, 0, 0, 0, 3, 0, 6, 0, 0},
        {0, 0, 0, 3, 0, 1, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 1, 4, 0},
        {0, 0, 0, 7, 0, 9, 0, 0, 0},
        {0, 0, 2, 0, 1, 0, 0, 0, 3},
        {9, 0, 0, 0, 0, 0, 5, 0, 7},
        {6, 7, 0, 4, 0, 0, 0, 0, 0}
    };

    std::vector<std::vector<int>> board3 = {
        {7, 2, 0, 0, 9, 6, 0, 0, 3},
        {0, 0, 0, 2, 0, 5, 0, 0, 0},
        {0, 8, 0, 0, 0, 4, 0, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 6, 0},
        {1, 0, 6, 5, 0, 3, 8, 0, 7},
        {0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 0, 8, 0, 0, 0, 9, 0},
        {0, 0, 0, 7, 0, 2, 0, 0, 0},
        {2, 0, 0, 4, 3, 0, 0, 1, 8}
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

    SudokuBoard m_board3{board3};
    std::cout << "Third Sudoku Board:\n";
    m_board3.printBoard();
    if (solveSudokuHuman(m_board3)) {
        std::cout << "Sudoku solved successfully:\n";
        m_board3.printBoard();
    } else {
        std::cout << "No solution exists.\n";
        m_board3.printBoard();
    }

    return 0;
}
