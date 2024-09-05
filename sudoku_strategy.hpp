#ifndef SUDOKU_STRATEGY_HPP
#define SUDOKU_STRATEGY_HPP

#include <string>
#include <iostream>
#include "sudoku_board.hpp"
#include "constraints.hpp"

class SudokuStrategy {
public:
    virtual bool apply(SudokuBoard& board, Constraints& constraints) = 0; // Pure virtual function
    virtual void print() const = 0;
    virtual std::string name() const = 0;  // To return the name of the strategy
    virtual ~SudokuStrategy() {}  // Virtual destructor for proper cleanup
};

#endif