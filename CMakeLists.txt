cmake_minimum_required(VERSION 3.10)
project(ReforestationSimulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where your header files are
include_directories(include)

# Define your executable and where its source files are
add_executable(simulation src/main.cpp)
