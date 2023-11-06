cmake_minimum_required(VERSION 3.23)
project(HF7_skeleton)

set(CMAKE_CXX_STANDARD 20)

add_executable(HF7_skeleton main.cpp sparsematrix.hpp sor.h list.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")