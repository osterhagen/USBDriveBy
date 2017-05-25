cmake_minimum_required(VERSION 3.6)
project(startercode_4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    brute.cpp
    brute.hpp
    encrypt.cpp
    key.hpp
    symbol.cpp
    symbol.hpp
    timer.hpp)

add_executable(startercode_4 ${SOURCE_FILES})