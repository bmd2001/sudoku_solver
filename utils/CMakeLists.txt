# Specify the include directory for this library
# No library is created because there's no .cpp file yet

# Add a target for the header-only library
# This is optional and only useful if you need to specify additional properties
add_library(utils_lib INTERFACE)

# Specify include directories for this header-only library
target_include_directories(utils_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})