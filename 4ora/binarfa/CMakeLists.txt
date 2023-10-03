cmake_minimum_required(VERSION 3.26)
project(binarfa)

set(CMAKE_CXX_STANDARD 17)

add_executable(binarfa main.cpp
        bs_tree.h
        exceptions.h)
