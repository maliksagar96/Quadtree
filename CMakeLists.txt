cmake_minimum_required(VERSION 3.10)

project(Quadtree)

set(target_name quadtree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(sources
  src/main.cpp
  src/quadtree.cpp
)

add_executable(${target_name} ${sources})
target_include_directories(${target_name} PRIVATE include)
