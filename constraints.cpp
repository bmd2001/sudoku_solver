#include "constraints.hpp"

Constraints::Constraints(SudokuBoard& board):
    board_(board)
    {
    std::map<int, std::map<int, std::set<int>>> result;

    auto gen = board.getBoardIterator();
    while (auto pair = gen.next()) {
        std::pair<int, int> row_col = pair->first;
        int row = row_col.first;
        int col = row_col.second;
        int num = pair->second;

        if (num != 0){
            result[row][col] = std::set<int>();
        }
        else{
            std::set<int> constraints;
            for (int num = 1; num < board.N+1; ++num){
                if (board.isCellSafe(row, col, num)){
                    constraints.insert(num);
                }
            }
            result[row][col] = constraints;
        }
    }

    map_ = result;
}

std::map<int, std::set<int>>& Constraints::operator[](int index){
    return map_[index];
}

void Constraints::modify(int row, int col){
    int num = board_[row][col];
    auto gen = board_.getCellInfluenceIterator(row, col);
    while (auto cell_pair = gen.next()) {
        std::pair<int, int> row_col = cell_pair->first;
        int row = row_col.first;
        int col = row_col.second;
        (*this)[row][col].erase(num);
    }
}