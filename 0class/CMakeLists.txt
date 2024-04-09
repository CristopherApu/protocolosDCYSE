cmake_minimum_required(VERSION 3.22)
project(0class)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(0class
        main.cpp
        operaciones.cpp
        struct.h)
