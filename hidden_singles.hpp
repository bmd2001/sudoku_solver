#ifndef HIDDEN_SINGLES_HPP
#define HIDDEN_SINGLES_HPP

#include "sudoku_strategy.hpp"
#include "utils.hpp"

class HiddenSingles : public SudokuStrategy{

    bool apply(SudokuBoard& board, Constraints& constraints) override{
        bool result = false;
        hidden_singles.clear();

        for (int i = 0; i < board.N; ++i) {
            // Initialize vector of shared pointers to Generator objects
            std::vector<std::pair<Generator<std::pair<std::pair<int, int>, std::set<int>>>, std::string>> cons_generators;

            cons_generators.emplace_back(constraints.getRowConstraints(i), "row");
            cons_generators.emplace_back(constraints.getColumnConstraints(i), "column");
            cons_generators.emplace_back(constraints.getBoxConstraints(i), "box");

            // Iterate over the generators using pointers
            for (auto& [cons, type] : cons_generators) {

                // Iterate over the elements yielded by the generator
                for (const auto& [pair, num] : findUniqueElements(cons)) {
                    result = true;
                    int row = pair.first;
                    int col = pair.second;

                    board[row][col] = num;
                    constraints.modify(row, col, num);

                    hidden_singles.emplace_back(type, i + 1, num, row + 1, col + 1);
                }
            }
        }

        return result;
    };

    void print() const override{
        std::cout << name() << ":\n";
        if (hidden_singles.empty()) {
            std::cout << "None";
        } else {
            for (const auto& [type, index, num, row, col] : hidden_singles) {
                std::cout << "In " << type << " " << index << ", "
                            << "the number " << num << " can only be placed in cell (" 
                            << row << ", " << col << ")\n";
            }
            std::cout << std::endl;
        }
    };

    std::string name() const override {
        return "Hidden Singles";
    };

    private:
        std::vector<std::tuple<std::string, int, int, int, int>> hidden_singles;
        
};

#endif