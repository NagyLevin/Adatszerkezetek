cmake_minimum_required(VERSION 3.26)
project(hf08)

set(CMAKE_CXX_STANDARD 20)

add_executable(hf08 main.cpp graphsolver.hpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")