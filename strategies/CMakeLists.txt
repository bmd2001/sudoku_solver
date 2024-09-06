# Define the library for src files
add_library(strategies_lib STATIC
    hidden_singles.cpp
    naked_singles.cpp
    naked_groups.cpp
)

# Specify include directories for this header-only library
target_include_directories(strategies_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/utils
)