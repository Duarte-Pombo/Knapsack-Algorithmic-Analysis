cmake_minimum_required(VERSION 3.26)
project(Project02 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type
set(CMAKE_BUILD_TYPE "Release")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/"docs")

# Source directory
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Automatically find all .cpp files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

# Set compilation flags for warnings and debugging
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")

# Set output directory for the built executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Define the executable with all source files
add_executable(Project02 ${SRC_FILES})

