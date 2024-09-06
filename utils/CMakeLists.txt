# Define the library for src files
add_library(utils_lib STATIC
    utils.cpp
)

# Specify include directories for this header-only library
target_include_directories(utils_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(utils_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src     # Include src if utils_lib needs headers from src
    ${CMAKE_SOURCE_DIR}/strategies  # Include strategies if utils_lib needs headers from strategies
)