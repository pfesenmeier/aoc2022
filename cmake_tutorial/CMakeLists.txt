cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(sample_project VERSION 1.0)

set(VAR "defined_in_cmakelists")

configure_file(Sample.h.in Sample.h)
# target_include_directories()

add_executable(sample sample.cpp)

