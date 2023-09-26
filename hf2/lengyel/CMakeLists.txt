cmake_minimum_required(VERSION 3.26)
project(lengyel)

set(CMAKE_CXX_STANDARD 17)

add_executable(lengyel main.cpp
        PolishNotation.cpp
        PolishNotation.h)
