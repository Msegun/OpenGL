cmake_minimum_required(VERSION 3.15)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lglut")
set(CMAKE_CXX_FLAGS "-lGL")
set(CMAKE_CXX_FLAGS "-lGLEW")

add_executable(Lab3 lab5zad1.cpp shader_stuff.h texture_loader.hpp glm)
# -lGLU mozna dodac
target_link_libraries(Lab3 -lglut -lGL -lGLEW)
