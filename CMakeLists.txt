cmake_minimum_required(VERSION 3.21)
project(cwk2)

set(CMAKE_C_STANDARD 11)
# SDL2
find_package(SDL2 REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS})


add_executable(cwk2 src/routeFinding.c src/visualization.c include/visualization.h src/main.c)
target_link_libraries(cwk2 ${SDL2_LIBRARIES})

# testing
add_executable(unittest src/unittest1.c src/routeFinding.c src/visualization.c include/visualization.h )
target_link_libraries(unittest ${SDL2_LIBRARIES} cunit)

