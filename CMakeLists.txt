cmake_minimum_required(VERSION 3.29)
include(cmake/vcpkg_install.cmake)

project(honeycomb LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
add_executable(honeycomb_exe src/main.cpp)
target_link_libraries(honeycomb_exe PRIVATE honeycomb_lib)
