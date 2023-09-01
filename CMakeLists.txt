# CMake info
cmake_minimum_required(VERSION 3.22)

project("zydeco")


# Locations
set(SOURCE_DIR "src")
set(LIB_SOURCE_DIR "lib/src")
set(INCLUDE_DIR
    "lib/include"
    "include"
    "include/events"
    "include/render"
    "include/runtime"
    "include/sdl2"
)


# Compile settings
set(CMAKE_CXX_STANDARD 20)
set(COMPILE_OPTIONS "-O3 -Wall -Wextra -pedantic")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
endif ()


# Add source files
include_directories(${INCLUDE_DIR})
set(PROGRAM_SOURCES
    "${LIB_SOURCE_DIR}/gl3w.c"
    "${SOURCE_DIR}/main.cpp"
    "${SOURCE_DIR}/Engine.cpp"
    "${SOURCE_DIR}/render/Renderer.cpp"
    "${SOURCE_DIR}/runtime/ThreadLooping.cpp"
    "${SOURCE_DIR}/sdl2/EventHandlerSDL2.cpp"
    "${SOURCE_DIR}/sdl2/WindowSDL2.cpp"
    "${SOURCE_DIR}/util/Fault.cpp"
    "${SOURCE_DIR}/util/Logger.cpp"
)


# Link libraries
find_package(cpptrace REQUIRED)
link_libraries("fmt" "cpptrace::cpptrace" "SDL2" "GL")


# Output
add_executable("zydeco" ${PROGRAM_SOURCES})
