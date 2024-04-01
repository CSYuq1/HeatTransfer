cmake_minimum_required(VERSION 3.28)
project(HeatTransfer)

set(CMAKE_CXX_STANDARD 26)

add_executable(
    TeatTransfer main.cpp
        src/heat_transfer_algorithm.cpp
        src/heat_transfer_algorithm.h
        src/solution.cpp
        src/solution.h
        teacher_solution/4_5.cpp
        teacher_solution/Ex4_2.cpp

)
