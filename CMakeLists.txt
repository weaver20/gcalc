cmake_minimum_required(VERSION 3.16)
project(gcalc)

set(CMAKE_CXX_STANDARD 11)

add_executable(gcalc
        gcalc/Graph.cpp
        gcalc/Auxilaries.cpp
        gcalc/Calc.cpp
        gcalc/main.cpp
        gcalc/Exception.cpp
        gcalc/GraphException.cpp)