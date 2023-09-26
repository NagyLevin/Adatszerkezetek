cmake_minimum_required(VERSION 3.26)
project(hibakezel)

set(CMAKE_CXX_STANDARD 17)

add_executable(hibakezel main.cpp
        custom_thrower.h
        custom_exception.h)
