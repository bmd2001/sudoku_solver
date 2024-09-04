cmake_minimum_required(VERSION 3.10)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 20)

# Add all .cpp files in the directory
file(GLOB SOURCES "*.cpp")

add_executable(sudoku_solver ${SOURCES})