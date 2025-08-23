set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/thirdparty/vcpkg")
set(VCPKG_BINARY "${VCPKG_ROOT}/vcpkg")

#Todo check for system installed vcpkg and use that instead if found

# Bootstrap vcpkg if necessary - this insures that the vcpkg executable exists
# and is built for the host platform.
if (NOT EXISTS "${VCPKG_BINARY}")
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
endif ()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake")