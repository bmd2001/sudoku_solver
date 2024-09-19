# Define the library for src files
add_library(src_lib STATIC
    sudoku_board.cpp
    constraints.cpp
)

# Specify include directories for this library
target_include_directories(src_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/utils    
    ${CMAKE_SOURCE_DIR}/strategies  
)

# Add subdirectory for tests
add_subdirectory(tests)