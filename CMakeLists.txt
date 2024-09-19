# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name
project(SudokuSolver)

# Define the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
message(STATUS "LCOV_PATH: ${LCOV_PATH}")
message(STATUS "GENHTML_PATH: ${GENHTML_PATH}")

# Set the path for custom CMake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules/)

# Enable testing
enable_testing()

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Add subdirectories
add_subdirectory(src)
add_subdirectory(strategies)
add_subdirectory(utils)

# Define the main executable
add_executable(SudokuSolver src/sudoku_solver.cpp)

# Link libraries to the executable
target_link_libraries(SudokuSolver PRIVATE src_lib strategies_lib utils_lib)

find_program(CPPCHECK_EXECUTABLE cppcheck PATHS "/usr/local/bin")

if (CPPCHECK_EXECUTABLE)
    add_custom_target(cppcheck
        COMMAND ${CPPCHECK_EXECUTABLE} --check-level=exhaustive --inconclusive --quiet --suppress=missingIncludeSystem
                --project=${CMAKE_BINARY_DIR}/compile_commands.json
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running cppcheck on the source files"
    )
else()
    message(WARNING "cppcheck executable not found. Install cppcheck to use this target.")
endif()

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure || true
    DEPENDS test_src # Add other test targets here
    COMMENT "Running all unit tests"
)