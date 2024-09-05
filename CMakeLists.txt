# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name
project(SudokuSolver)

# Define the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(strategies)
add_subdirectory(utils)

# Define the main executable
add_executable(SudokuSolver src/sudoku_solver.cpp)

# Link libraries to the executable
target_link_libraries(SudokuSolver PRIVATE src_lib strategies_lib utils_lib)