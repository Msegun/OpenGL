cmake_minimum_required(VERSION 3.15)
project(movingSpheres)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lglut")
set(CMAKE_CXX_FLAGS "-lGL")
set(CMAKE_CXX_FLAGS "-lGLU")

add_executable(movingSpheres main.cpp Sphere.cpp Sphere.h)
target_link_libraries(movingSpheres -lglut -lGL -lGLU)