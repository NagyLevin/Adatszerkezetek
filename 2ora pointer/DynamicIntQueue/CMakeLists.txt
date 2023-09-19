cmake_minimum_required(VERSION 3.26)
project(DynamicIntQueue)

set(CMAKE_CXX_STANDARD 17)

add_executable(DynamicIntQueue main.cpp
        DynamicIntQueue.cpp
        DynamicIntQueue.h)
