# Define the library for src files
add_library(src_lib STATIC
    sudoku_board.cpp
    constraints.cpp
)

# Specify include directories for this library
target_include_directories(src_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})