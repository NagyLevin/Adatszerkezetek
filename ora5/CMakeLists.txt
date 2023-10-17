cmake_minimum_required(VERSION 3.26)
project(ora5)

set(CMAKE_CXX_STANDARD 17)

add_executable(ora5 main.cpp
        avltree.h
        exceptions.h)
