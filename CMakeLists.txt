cmake_minimum_required(VERSION 3.29)
project(honeycomb LANGUAGES CXX)

include(cmake/vcpkg_install.cmake)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build catch unit tests ." ON)

find_package(VTK REQUIRED COMPONENTS
        CommonCore
        CommonDataModel
        FiltersCore
        IOXML
        RenderingCore
        RenderingOpenGL2
        InteractionStyle
)

add_library(honeycomb_lib STATIC
        src/lib/honeycomb.cpp
        src/lib/honeycomb.h
        src/lib/skeleton_2d.cpp
        src/lib/skeleton_2d.h
        src/lib/vtk_renderer.cpp
        src/lib/vtk_renderer.h
)

target_include_directories(honeycomb_lib PUBLIC src/lib)

target_link_libraries(honeycomb_lib PRIVATE
        VTK::CommonCore
        VTK::CommonDataModel
        VTK::FiltersCore
        VTK::IOXML
        VTK::RenderingCore
        VTK::RenderingOpenGL2
        VTK::InteractionStyle
)

vtk_module_autoinit(
        TARGETS honeycomb_lib
        MODULES VTK::CommonCore
                VTK::CommonDataModel
                VTK::FiltersCore
                VTK::IOXML
                VTK::RenderingCore
                VTK::RenderingOpenGL2
                VTK::InteractionStyle
)

find_package(cxxopts REQUIRED)
add_executable(honeycomb_exe src/main.cpp)
target_link_libraries(honeycomb_exe PRIVATE honeycomb_lib cxxopts::cxxopts)


if (BUILD_TESTS)
    find_package(Catch2 REQUIRED)
    add_executable(honeycomb_tests
            src/lib/skeleton_2d.test.cpp
            src/lib/honeycomb.test.cpp
    )
    target_link_libraries(honeycomb_tests PRIVATE honeycomb_lib Catch2::Catch2WithMain)
    add_test(NAME honeycomb_tests COMMAND honeycomb_tests)
endif()