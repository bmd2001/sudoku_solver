#include "sudoku_strategy.hpp"

class NakedSingles : public SudokuStrategy{

    public:
        bool apply(SudokuBoard& board, Constraints& constraints) override;
        void print() const override;
        std::string name() const override;

    private:
        std::vector<std::tuple<int, int, int>> naked_singles;
};
