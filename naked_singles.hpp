#include "constraints.hpp"

bool nakedSingles(SudokuBoard& board, Constraints& constraints){

    std::vector<std::pair<int, int>> naked_singles;

    for (auto pair : board.getBoardIterator()) {
        std::pair<int, int> row_col = pair.first;
        int row = row_col.first;
        int col = row_col.second;

        std::set<int> cons = constraints[row][col];
        if (cons.size() == 1){
            naked_singles.push_back(row_col);
            board[row][col] = *cons.begin();
        }
    }

    for (auto row_col_pair : naked_singles){
        int row = row_col_pair.first;
        int col = row_col_pair.second;
        constraints.modify(row, col, board[row][col]);
        std::cout << "At (" << row+1 << ", " << col+1 << "), " << board[row][col] << " is the only number that can be placed" << std::endl;
    }

    return !naked_singles.empty();

}