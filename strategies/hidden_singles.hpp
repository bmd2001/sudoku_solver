#ifndef HIDDEN_SINGLES_HPP
#define HIDDEN_SINGLES_HPP

#include "sudoku_strategy.hpp"

class HiddenSingles : public SudokuStrategy{

    public:
        bool apply(SudokuBoard& board, Constraints& constraints) override;
        void print() const override;
        std::string name() const override;

    private:
        std::vector<std::tuple<std::string, int, int, int, int>> hidden_singles;
        
};

#endif