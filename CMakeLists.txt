cmake_minimum_required(VERSION 3.27)
project(HeatTransfer)

set(CMAKE_CXX_STANDARD 23)

add_executable(
    TeatTransfer main.cpp
        src/solution4_12.cpp
        src/heat_transfer_algorithm.h

)
