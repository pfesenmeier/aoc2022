cmake_minimum_required(VERSION 3.24)
project(day7)

set(CMAKE_CXX_STANDARD 20)

# library.h
include_directories(/home/pfese/aoc2022/aoc_lib/)

#link_directories(/home/pfese/aoc2022/aoc_lib/)
add_executable(day7 main.cpp)

# libaoc_lib.so
find_library(AOC_LIB libaoc_lib /home/pfese/aoc2022/aoc_lib/cmake-build-debug/)
target_link_libraries(day7 LINK_PUBLIC ${aoc_lib})
