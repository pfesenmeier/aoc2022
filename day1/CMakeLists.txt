cmake_minimum_required(VERSION 3.24)
project(day1)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(day1 main.cpp)

target_link_libraries(
        day1
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day1)