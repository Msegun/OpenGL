cmake_minimum_required(VERSION 3.15)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lglut")
set(CMAKE_CXX_FLAGS "-lGL")
set(CMAKE_CXX_FLAGS "-lGLU")

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1 chessboard.cpp)
target_link_libraries(Lab1 -lglut -lGL -lGLU)