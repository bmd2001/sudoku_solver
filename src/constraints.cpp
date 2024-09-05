#include "constraints.hpp"

Constraints::Constraints(SudokuBoard& board):
    board_(board)
    {
    std::map<int, std::map<int, std::set<int>>> result;

    for (auto pair : board.getBoardIterator()) {
        std::pair<int, int> row_col = pair.first;
        int row = row_col.first;
        int col = row_col.second;
        int num = pair.second;

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

void Constraints::modify(int row, int col, int num){
    for (auto cell_pair : board_.getCellInfluenceIterator(row, col)) {
        std::pair<int, int> row_col = cell_pair.first;
        int row_2_modify = row_col.first;
        int col_2_modify = row_col.second;
        (*this)[row_2_modify][col_2_modify].erase(num);
    }
    (*this)[row][col].clear();
}

Generator<std::pair<std::pair<int, int>, std::set<int>>> Constraints::getRowConstraints(int row){
    for (auto& [key, value] : map_[row]) {
        if (!value.empty()){
            co_yield {{row, key}, value};
        }
    }
}

Generator<std::pair<std::pair<int, int>, std::set<int>>> Constraints::getColumnConstraints(int col){
    for (auto& [key, value] : map_) {
        for (auto& [map_col, con] : value) {
            if (map_col == col && !con.empty()){
                co_yield {{key, col}, con};
            }
        }
    }
}

Generator<std::pair<std::pair<int, int>, std::set<int>>> Constraints::getBoxConstraints(int box){
    int startRow = (box / 3)*3;
    int startCol = (box % 3)*3;

    for (int r = startRow; r < startRow + 3; ++r) {
        for (int c = startCol; c < startCol + 3; ++c) {
            std::set<int>& con = map_[r][c];
            if (!con.empty()) {
                co_yield {{r, c}, con};
            }
        }
    }
}