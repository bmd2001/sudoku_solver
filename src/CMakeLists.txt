# Define the library for src files
add_library(src_lib STATIC
    sudoku_board.cpp
    constraints.cpp
    sudoku_solver.cpp
)

# Specify include directories for this library
target_include_directories(src_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src     # Include src if utils_lib needs headers from src
    ${CMAKE_SOURCE_DIR}/strategies  # Include strategies if utils_lib needs headers from strategies
)