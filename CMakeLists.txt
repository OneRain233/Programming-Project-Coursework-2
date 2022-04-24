cmake_minimum_required(VERSION 3.21)
project(cwk2)

set(CMAKE_C_STANDARD 11)
# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(cwk2 dij.c visualization.c visualization.h main.c main.h)
target_link_libraries(cwk2 ${SDL2_LIBRARIES})
