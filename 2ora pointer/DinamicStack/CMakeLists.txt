cmake_minimum_required(VERSION 3.26)
project(DinamicStack)

set(CMAKE_CXX_STANDARD 17)

add_executable(DinamicStack main.cpp
        DynamicIntStack.cpp
        DynamicIntStack.h)
