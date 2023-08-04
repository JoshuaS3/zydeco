# CMake info
cmake_minimum_required(VERSION 3.22)

project("zydeco")


# Locations
set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")


# Compile settings
set(CMAKE_CXX_STANDARD 20)
set(COMPILE_OPTIONS "-O3 -Wall -Wextra -pedantic")


# Add source files
include_directories(${INCLUDE_DIR})
set(PROGRAM_SOURCES
    "${SOURCE_DIR}/main.cpp"
    "${SOURCE_DIR}/util/Logger.cpp"
    "${SOURCE_DIR}/util/Fault.cpp"
    "${SOURCE_DIR}/game/Window.cpp"
)


# Link libraries
find_package(cpptrace REQUIRED)
link_libraries("fmt" "SDL2" "cpptrace::cpptrace")


# Output
add_executable("zydeco" ${PROGRAM_SOURCES})
