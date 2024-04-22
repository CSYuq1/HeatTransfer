cmake_minimum_required(VERSION 3.27)
project(HeatTransfer)
set(CMAKE_CXX_STANDARD 23)
add_executable(
    debug main.cpp
        src/solution4_12.cpp
        src/solution4_6.cpp
)
