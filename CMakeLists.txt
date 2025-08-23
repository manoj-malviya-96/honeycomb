cmake_minimum_required(VERSION 3.29)

include(cmake/vcpkg_install.cmake) # handles vcpkg bootstrap and integration

project(honeycomb LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)
add_executable(honeycomb
        src/main.cpp)