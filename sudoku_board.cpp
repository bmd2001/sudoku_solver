#include "sudoku_board.hpp"

#define N 9

SudokuBoard::SudokuBoard(std::vector<std::vector<int>> board)
    :m_board(board){};

std::vector<int>& SudokuBoard::operator[](int index){
    return m_board[index];
}

void SudokuBoard::printBoard() const{
    for (const auto& row : m_board) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

bool SudokuBoard::isSafe(int row, int col, int num){
    for (int cell: this->getCellInfluenceIterator(row, col)){
        if (cell == num){
            return false;
        }
    }
    return true;
}

std::vector<int> SudokuBoard::getCellInfluenceIterator(int row, int col) {

    std::vector<int> cells_;

    for (int x = 0; x < N; ++x) {
        if (x != col){
            cells_.push_back((*this)[row][x]);
        }
        if (x != row){
            cells_.push_back((*this)[x][col]);
        }
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int r = startRow; r < startRow + 3; ++r) {
        for (int c = startCol; c < startCol + 3; ++c) {
            if (r != row && c != col) {
                cells_.push_back((*this)[r][c]);
            }
        }
    }

    return cells_;
}
