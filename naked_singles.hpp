#include "sudoku_board.hpp"
#include "constraints.hpp"


bool nakedSingles(SudokuBoard& board, Constraints& constraints){

    std::vector<std::pair<int, int>> naked_singles;

    auto gen = board.getBoardIterator();
    while (auto pair = gen.next()) {
        std::pair<int, int> row_col = pair->first;
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
        constraints.modify(row, col);
    }

    return !naked_singles.empty();

}