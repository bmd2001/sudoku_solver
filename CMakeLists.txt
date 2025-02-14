# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name
project(SudokuSolver)

# Define the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

# Find the lcov and genhtml paths
set(CMAKE_C_COMPILER "/usr/local/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")
set(LLVM_COV_EXECUTABLE "/usr/local/opt/llvm/bin/llvm-cov")
set(LLVM_PROFDATA_EXECUTABLE "/usr/local/opt/llvm/bin/llvm-profdata")
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)
if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-instr-generate")
endif()

# Check if lcov and genhtml paths are provided (set via environment variables)
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "LLVM_COV_EXECUTABLE: ${LLVM_COV_EXECUTABLE}")
message(STATUS "LCOV_PATH: ${LCOV_PATH}")
message(STATUS "GENHTML_PATH: ${GENHTML_PATH}")
message(STATUS "CMAKE_CTEST_COMMAND: ${CMAKE_CTEST_COMMAND}")

# Add custom target for coverage
add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E env LLVM_PROFILE_FILE=${CMAKE_BINARY_DIR}/coverage.profraw ${CMAKE_CTEST_COMMAND} --output-on-failure || true
    COMMAND ${LLVM_PROFDATA_EXECUTABLE} merge ${CMAKE_BINARY_DIR}/coverage.profraw -output=${CMAKE_BINARY_DIR}/coverage.profdata
    COMMAND ${LLVM_COV_EXECUTABLE} export -format=lcov ${CMAKE_BINARY_DIR}/src/tests/test_src --instr-profile=${CMAKE_BINARY_DIR}/coverage.profdata > ${CMAKE_BINARY_DIR}/coverage.info
    COMMAND ${LCOV_PATH} --capture --directory ${CMAKE_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info
    COMMAND ${GENHTML_PATH} ${CMAKE_BINARY_DIR}/coverage.info --output-directory ${CMAKE_BINARY_DIR}/coverage_report
    COMMENT "Generating coverage report"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    USES_TERMINAL
)
