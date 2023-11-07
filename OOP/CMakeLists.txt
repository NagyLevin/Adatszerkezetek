cmake_minimum_required(VERSION 3.26)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP main.cpp
        car.h
        Taxi.h
        Bus.h
        Bike.h
        Vehicle.h)
