cmake_minimum_required(VERSION 3.26)
project(adatszerk_hf01)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")

add_executable(adatszerk_hf01 main.cpp
        bracketchecker.cpp
        bracketchecker.h)
