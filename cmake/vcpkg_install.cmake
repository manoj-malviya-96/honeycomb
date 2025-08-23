

option(PREFER_SYSTEM_VCPKG "Prefer using system-installed vcpkg over vendored copy" OFF)

function(config_system_vcpkg)
    find_program(SYSTEM_VCPKG NAMES vcpkg)

    if (NOT SYSTEM_VCPKG OR NOT EXISTS "${SYSTEM_VCPKG}")
        message(STATUS "vcpkg not found in PATH")
        return()
    endif()

    message(STATUS "Using system-installed vcpkg: ${SYSTEM_VCPKG}")
    set(VCPKG_BINARY "${SYSTEM_VCPKG}")
    get_filename_component(VCPKG_ROOT "${VCPKG_BINARY}/.." ABSOLUTE)

    set(VCPKG_ROOT "${VCPKG_ROOT}" PARENT_SCOPE)
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endfunction()


function(config_vendored_vcpkg)
    set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/vcpkg")
    set(VCPKG_BINARY  "${VCPKG_ROOT}/vcpkg")

    if (NOT EXISTS "${VCPKG_ROOT}/vcpkg")
        message(STATUS "Bootstrapping vcpkg in ${VCPKG_ROOT}…")
        execute_process(
                COMMAND "${VCPKG_ROOT}/bootstrap-vcpkg.sh"
                WORKING_DIRECTORY "${VCPKG_ROOT}"
                RESULT_VARIABLE _vcpkg_bootstrap_res
                OUTPUT_VARIABLE _vcpkg_bootstrap_out
                ERROR_VARIABLE _vcpkg_bootstrap_err
        )
        if (NOT _vcpkg_bootstrap_res EQUAL 0)
            message(FATAL_ERROR
                    "vcpkg bootstrap failed:\n${_vcpkg_bootstrap_err}\n${_vcpkg_bootstrap_out}")
        endif ()
    endif()
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" PARENT_SCOPE)
endfunction()


# If the user prefers system vcpkg, try to find it first.
if(PREFER_SYSTEM_VCPKG)
    message(STATUS "PREFER_SYSTEM_VCPKG is ON, trying to find system-installed vcpkg first")
    setup_system_vcpkg()
endif()

if (NOT EXISTS "${VCPKG_BINARY}")
    message(STATUS "Using vendored vcpkg")
    config_vendored_vcpkg()
endif()


set(VCPKG_FEATURE_FLAGS "binarycaching")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_PROGRESS_REPORT ON)
set(VCPKG_VERBOSE "1" CACHE STRING "Enable verbose output from vcpkg" FORCE)