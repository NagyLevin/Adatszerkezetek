cmake_minimum_required(VERSION 3.26)
project(lancoltlista)

set(CMAKE_CXX_STANDARD 17)

add_executable(lancoltlista main.cpp
        list.h
        listexception.h)
