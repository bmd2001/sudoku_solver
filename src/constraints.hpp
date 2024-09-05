#ifndef CONSTRAINTS_HPP
#define CONSTRAINTS_HPP

#include <set>
#include <map>
#include "sudoku_board.hpp"

class Constraints{

    public:

        Constraints(SudokuBoard& board);

        std::map<int, std::set<int>>& operator[](int);
        void modify(int row, int col, int num);

        Generator<std::pair<std::pair<int, int>, std::set<int>>> getRowConstraints(int row);
        Generator<std::pair<std::pair<int, int>, std::set<int>>> getColumnConstraints(int col);
        Generator<std::pair<std::pair<int, int>, std::set<int>>> getBoxConstraints(int box);
    
    private:
        SudokuBoard& board_;
        std::map<int, std::map<int, std::set<int>>> map_;
     
};

#endif
