#include "sudoku_strategy.hpp"

class NakedSingles : public SudokuStrategy{

    bool apply(SudokuBoard& board, Constraints& constraints) override{
        naked_singles.clear();

        for (auto pair : board.getBoardIterator()) {
            std::pair<int, int> row_col = pair.first;
            int row = row_col.first;
            int col = row_col.second;

            std::set<int> cons = constraints[row][col];
            if (cons.size() == 1){
                int num = *cons.begin();
                naked_singles.emplace_back(row+1, col+1, num);
                board[row][col] = num;
            }
        }

        for (const auto& [row, col, num] : naked_singles){
            constraints.modify(row-1, col-1, num);
        }

        return !naked_singles.empty();
    };

    void print() const override{
        std::cout << name() << ":\n";
        if (naked_singles.empty()) {
            std::cout << "None\n";
        } else {
            for (const auto& [row, col, num] : naked_singles) {
                std::cout << "At (" << row << ", " << col << "), " 
                << num << " is the only number that can be placed\n";
            }
            std::cout << std::endl;
        }
    };

    std::string name() const override {
        return "Naked Singles";
    };

    private:
        std::vector<std::tuple<int, int, int>> naked_singles;
        
};