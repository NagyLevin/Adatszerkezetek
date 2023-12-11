cmake_minimum_required(VERSION 3.26)
project(potzhgyak)

set(CMAKE_CXX_STANDARD 17)

add_executable(potzhgyak  main.cpp
        FixedSor.h
        FixedVerem.h
        DinamicVerem.h
        DinamicSor.h
        2xList.h
        binfa.h
        awltree.h
        zhpelda.h)
