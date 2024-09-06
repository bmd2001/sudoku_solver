#ifndef NAKED_GROUPS_HPP
#define NAKED_GROUPS_HPP

#include "sudoku_strategy.hpp"

typedef std::vector<std::vector<std::pair<Cell, std::set<int>>>> Combinations;
class NakedGroups : public SudokuStrategy{

    public:
        bool apply(SudokuBoard& board, Constraints& constraints) override;
        void print() const override;
        std::string name() const override;

    private:
        std::vector<std::tuple<std::string, int, std::vector<Cell>, std::set<int>>> naked_groups;
        std::set<std::pair<std::vector<Cell>, std::set<int>>> already_visited;
        std::pair<bool, std::set<int>> isGroupValid(std::vector<std::set<int>> candidates, int group_size, std::vector<Cell> cells);
        
};

#endif