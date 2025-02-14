#include <gtest/gtest.h>
#include "sudoku_board.hpp"

class SudokuBoardTest : public ::testing::Test {
protected:
    // Initialize pointers or default values
    SudokuBoard* empty_board;
    SudokuBoard* board;
    SudokuBoard* full_board;
    SudokuBoard* wrong_dimension_board;

    void SetUp() override {
        // Initialize boards here
        empty_board = new SudokuBoard(std::vector<std::vector<int>>(9, std::vector<int>(9, 0)));
        board = new SudokuBoard({
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        });
        full_board = new SudokuBoard({
            {5, 3, 4, 6, 7, 8, 9, 1, 2},
            {6, 7, 2, 1, 9, 5, 3, 4, 8},
            {1, 9, 8, 3, 4, 2, 5, 6, 7},
            {8, 5, 9, 7, 6, 1, 4, 2, 3},
            {4, 2, 6, 8, 5, 3, 7, 9, 1},
            {7, 1, 3, 9, 2, 4, 8, 5, 6},
            {9, 6, 1, 5, 3, 7, 2, 8, 4},
            {2, 8, 7, 4, 1, 9, 6, 3, 5},
            {3, 4, 5, 2, 8, 6, 1, 7, 9}
        });
        wrong_dimension_board = new SudokuBoard({
            {1, 2},
            {2, 1}
        });
    }

    void TearDown() override {
        delete empty_board;
        delete board;
        delete full_board;
        delete wrong_dimension_board;
    }
};

TEST_F(SudokuBoardTest, isBoardFull){
    ASSERT_FALSE(empty_board->isBoardFull());
    ASSERT_FALSE(board->isBoardFull());
    ASSERT_TRUE(full_board->isBoardFull());
    ASSERT_TRUE(wrong_dimension_board->isBoardFull());
}

TEST_F(SudokuBoardTest, isCellSafe) {
    ASSERT_TRUE(empty_board->isCellSafe(0, 0, 9));
    ASSERT_TRUE(board->isCellSafe(0, 2, 1));
    ASSERT_FALSE(board->isCellSafe(2, 0, 9));
    for (int i = 1; i <= full_board->N; ++i){
        ASSERT_FALSE(full_board->isCellSafe(0, 0, i));
    }
}

TEST_F(SudokuBoardTest, wrongDimensionAssignment){
    ASSERT_THROW(*board = *wrong_dimension_board, std::invalid_argument);
}

// Main function for Google Test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
