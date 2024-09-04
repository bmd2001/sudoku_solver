#ifndef CONSTRAINTS_HPP
#define CONSTRAINTS_HPP

#include <set>
#include <map>
#include "sudoku_board.hpp"

class Constraints{

    public:

        Constraints(SudokuBoard& board);

        std::map<int, std::set<int>>& operator[](int);
        void modify(int row, int col);
    
    private:
        SudokuBoard& board_;
        std::map<int, std::map<int, std::set<int>>> map_;
     
};

#endif
