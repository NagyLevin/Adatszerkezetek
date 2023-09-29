cmake_minimum_required(VERSION 3.14)
project(PolishNotation)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")

add_executable(PolishNotation
        main.cpp
        PolishNotation.h
        PolishNotation.cpp
        DynamicIntStack.h
        DynamicIntStack.cpp
        )
