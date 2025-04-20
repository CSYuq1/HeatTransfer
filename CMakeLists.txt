cmake_minimum_required(VERSION 3.27)
project(HeatTransfer)
set(CMAKE_CXX_STANDARD 23)
add_executable(4_6 solution4_6.cpp)
add_executable(4_12 solution4_12.cpp)
target_compile_options(4_6 PUBLIC -march=native)
target_compile_options(4_12 PUBLIC -march=native)

