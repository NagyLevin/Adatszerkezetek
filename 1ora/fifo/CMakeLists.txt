cmake_minimum_required(VERSION 3.24)
project(FIFO)

set(CMAKE_CXX_STANDARD 17)

add_executable(FIFO main.cpp FixedQueue.cpp FixedQueue.h)
