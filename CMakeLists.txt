cmake_minimum_required(VERSION 3.16)

# Project name and language
project(shopmaster VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers
include_directories(include)

# Collect all source files
file(GLOB SOURCES src/*.cpp)

# Create executable
add_executable(shopmaster ${SOURCES})

# Compiler warnings
if (MSVC)
    target_compile_options(shopmaster PRIVATE /W4)
else()
    target_compile_options(shopmaster PRIVATE -Wall -Wextra -pedantic)
endif()

# Output executable to a folder named 'eses' inside the build directory
set_target_properties(shopmaster PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/
)

# Optional: installation rule
install(TARGETS shopmaster DESTINATION bin)
