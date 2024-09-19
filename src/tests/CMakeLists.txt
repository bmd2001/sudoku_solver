# Add the test executable
add_executable(test_src
    sudoku_board_test.cpp
)

# Link the test executable with GTest and your project libraries
target_link_libraries(test_src
    GTest::GTest
    GTest::Main
    src_lib  # Replace with the actual name of your project's library
)

# Add the test to CTest
add_test(NAME SudokuBoardTest COMMAND test_src)
