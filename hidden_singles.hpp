#ifndef HIDDEN_SINGLES_HPP
#define HIDDEN_SINGLES_HPP

#include "constraints.hpp"
#include "utils.hpp"

bool hiddenSingles(SudokuBoard& board, Constraints& constraints){
    bool result = false;

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

                std::cout << "In " << type << " " << i+1 << ", "
                << "the number " << num << " can only be place in cell (" 
                << row+1 << ", " << col+1 << ")" << std::endl;
            }
        }
    }

    return result;
}

#endif