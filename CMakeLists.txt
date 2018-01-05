cmake_minimum_required(VERSION 3.5)
project(eNet)

set(CMAKE_CXX_STANDARD 11)

add_library(
        eNet
        src/eBuffer.cpp
        src/eSocket.cpp src/eTypes.hpp)
