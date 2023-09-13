cmake_minimum_required(VERSION 3.24)
project(lifo)

set(CMAKE_CXX_STANDARD 17)

add_executable(lifo main.cpp FixedStack.cpp FixedStack.h)
