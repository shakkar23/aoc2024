
cmake_minimum_required(VERSION 3.22)

project(aoc1)

set(CMAKE_CXX_STANDARD 23)

add_executable(aoc1 main.cpp)

file(COPY inputs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
