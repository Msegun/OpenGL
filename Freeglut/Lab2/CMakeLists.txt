cmake_minimum_required(VERSION 3.15)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lglut")
set(CMAKE_CXX_FLAGS "-lGL")
# set(CMAKE_CXX_FLAGS "-lGLU")
set(CMAKE_CXX_FLAGS "-lGLEW")

add_executable(Lab2 cube.cpp shader_stuff.h house.h glm)
# -lGLU mozna dodac
target_link_libraries(Lab2 -lglut -lGL -lGLEW)

