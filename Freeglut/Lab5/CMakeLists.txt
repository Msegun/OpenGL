cmake_minimum_required(VERSION 3.15)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lglut")
set(CMAKE_CXX_FLAGS "-lGL")
set(CMAKE_CXX_FLAGS "-lGLEW")

add_executable(Lab5 zad4.cpp GLProgram.cpp GLProgram.hpp shader_stuff.h obj_loader.hpp texture_loader.hpp glm)
# -lGLU mozna dodac
target_link_libraries(Lab5 -lglut -lGL -lGLEW)