cmake_minimum_required(VERSION 3.22)
project(hf09)

set(CMAKE_CXX_STANDARD 23)

add_executable(hf09 main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")
