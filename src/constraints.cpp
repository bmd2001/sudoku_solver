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
    generator_map_["row"] = [this](int i) { return this->getRowConstraints(i); };
    generator_map_["column"] = [this](int i) { return this->getColumnConstraints(i); };
    generator_map_["box"] = [this](int i) { return this->getBoxConstraints(i); };
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

void Constraints::modifyGroup(int index, std::string type, std::vector<Cell> cells, std::set<int> nums){
    auto generator = generator_map_[type](index);
    for (auto [pair, cons] : generator){
        int row = pair.first;
        int col = pair.second;
        if (std::find(cells.begin(), cells.end(), pair) != cells.end()){
            std::set<int> intersection;
            std::set_intersection(nums.begin(), nums.end(),
                          cons.begin(), cons.end(),
                          std::inserter(intersection, intersection.begin()));
            
            (*this)[row][col] = intersection;
        }
        else{
            std::set<int> difference;
            std::set_difference(cons.begin(), cons.end(),
                                nums.begin(), nums.end(),
                                std::inserter(difference, difference.begin()));
            (*this)[row][col] = difference;
        }
    }
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