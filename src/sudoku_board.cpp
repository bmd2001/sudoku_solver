#include "sudoku_board.hpp"
#include <coroutine>

SudokuBoard::SudokuBoard(const std::vector<std::vector<int>>& board)
    :N(board.size()), m_board(board)
    {

    };

std::vector<int>& SudokuBoard::operator[](int index){
    return m_board[index];
}

void SudokuBoard::printBoard() const{
    for (const auto& row : m_board) {
        for (int num : row) {
            if (num != 0){
                std::cout << num << " ";
            }
            else{
                std::cout << "_" << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool SudokuBoard::isBoardFull(){
    return std::all_of(m_board.begin(), m_board.end(), [](std::vector<int>& row){
                return std::all_of(row.begin(), row.end(), [](int cell){
                    return cell > 0;
                });
            });
}

bool SudokuBoard::isCellSafe(int row, int col, int num) const{
    auto iterator = this->getCellInfluenceIterator(row, col);
    return std::all_of(iterator.begin(), iterator.end(), [num](const auto& pair) {
        return pair.second != num;
    });
}

Generator<std::pair<std::pair<int, int>, int>> SudokuBoard::getBoardIterator() const{
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            co_yield {{row, col}, m_board[row][col]};
        }
    }
}

Generator<std::pair<std::pair<int, int>, int>> SudokuBoard::getCellInfluenceIterator(int row, int col) const{
    for (int x = 0; x < this->N; ++x) {
        if (x != col) {
            co_yield {{row, x}, m_board[row][x]};
        }
        if (x != row) {
            co_yield {{x, col}, m_board[x][col]};
        }
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int r = startRow; r < startRow + 3; ++r) {
        for (int c = startCol; c < startCol + 3; ++c) {
            if (r != row && c != col) {
                co_yield {{r, c}, m_board[r][c]};
            }
        }
    }
}
