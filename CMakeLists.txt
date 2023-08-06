# CMake info
cmake_minimum_required(VERSION 3.22)

project("zydeco")


# Locations
set(SOURCE_DIR "src")
set(INCLUDE_DIR "include" "include/sdl2" "include/events")


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
    "${SOURCE_DIR}/main.cpp"
    "${SOURCE_DIR}/Engine.cpp"
    "${SOURCE_DIR}/util/Fault.cpp"
    "${SOURCE_DIR}/util/Logger.cpp"
    "${SOURCE_DIR}/sdl2/EventHandlerSDL2.cpp"
    "${SOURCE_DIR}/sdl2/WindowSDL2.cpp"
)


# Link libraries
find_package(cpptrace REQUIRED)
link_libraries("fmt" "cpptrace::cpptrace" "SDL2" "GL")


# Output
add_executable("zydeco" ${PROGRAM_SOURCES})
