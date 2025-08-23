cmake_minimum_required(VERSION 3.29)
project(honeycomb)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
add_executable(honeycomb
        src/main.cpp)