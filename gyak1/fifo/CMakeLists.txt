cmake_minimum_required(VERSION 3.24)
project(fifo)


set(CMAKE_CXX_STANDARD 17)

add_executable(fifo main.cpp FixedQueue.cpp FixedQueue.h)
