cmake_minimum_required (VERSION 3.4)
project (strformat_test)

set(CMAKE_CONFIGURATION_TYPES "debug;release")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS "debug")

if (MSVC)
    add_definitions(
        -DWINVER=0x0601
        -D_WIN32_WINNT=0x0601
        -DWIN32_LEAN_AND_MEAN
        -DNOMINMAX
        -D_CRT_SECURE_NO_WARNINGS
        -D_CRT_NON_CONFORMING_SWPRINTFS
        -D_SCL_SECURE_NO_WARNINGS
    )

    string (FIND ${CMAKE_GENERATOR} "Win64" MSVC_X86_64)

    if (${MSVC_X86_64} EQUAL -1)
        set(MSVC_X86_64 0)
    else()
        set(MSVC_X86_64 1)
    endif()
endif()

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "$ENV{BENCHMARK_INCLUDE_DIR}"
    "$ENV{FMT_INCLUDE_DIR}"
    "$ENV{BOOST_INCLUDE_DIR}"
    "$ENV{FASTFORMAT_INCLUDE_DIR}"
    "$ENV{STLSOFT_INCLUDE_DIR}"     # required by fastformat
)

set (PROJECT_LIB_DIR "${PROJECT_SOURCE_DIR}/lib")
if (MSVC)
    if (MSVC_X86_64)
        set (LIBRARIES
            shlwapi.lib
            debug     "${PROJECT_LIB_DIR}/win64/debug/benchmark.lib"
            optimized "${PROJECT_LIB_DIR}/win64/release/benchmark.lib"
            debug     "${PROJECT_LIB_DIR}/win64/debug/fmt.lib"
            optimized "${PROJECT_LIB_DIR}/win64/release/fmt.lib"
            debug     "${PROJECT_LIB_DIR}/win64/debug/fastformat.0.core.vc14.x64.dll.debug.lib"
            optimized "${PROJECT_LIB_DIR}/win64/release/fastformat.0.core.vc14.x64.dll.lib"
        )
    else()
        set (LIBRARIES
            shlwapi.lib
            debug     "${PROJECT_LIB_DIR}/win32/debug/benchmark.lib"
            optimized "${PROJECT_LIB_DIR}/win32/release/benchmark.lib"
            debug     "${PROJECT_LIB_DIR}/win32/debug/fmt.lib"
            optimized "${PROJECT_LIB_DIR}/win32/release/fmt.lib"
            debug     "${PROJECT_LIB_DIR}/win32/debug/fastformat.0.core.vc14.dll.debug.lib"
            optimized "${PROJECT_LIB_DIR}/win32/release/fastformat.0.core.vc14.dll.lib"
        )
    endif()
endif()

set (SOURCE_FILES
    "main.cpp"
)

add_executable("${PROJECT_NAME}" ${SOURCE_FILES})

target_link_libraries (${PROJECT_NAME} ${LIBRARIES})
