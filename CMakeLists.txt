# CMake info
cmake_minimum_required(VERSION 3.22)

project("zydeco")


# Locations
set(SOURCE_DIR "src")
set(LIB_SOURCE_DIR "lib")
set(INCLUDE_DIR
    "lib/imgui"
    "lib/gl3w/include"
    "include"
    "include/events"
    "include/render"
    "include/render/gl"
    "include/render/objects"
    "include/render/shaders"
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

set(LIB_SOURCES
    "${LIB_SOURCE_DIR}/gl3w/src/gl3w.c"
    "${LIB_SOURCE_DIR}/imgui/imgui.cpp"
    "${LIB_SOURCE_DIR}/imgui/imgui_demo.cpp"
    "${LIB_SOURCE_DIR}/imgui/imgui_draw.cpp"
    "${LIB_SOURCE_DIR}/imgui/imgui_tables.cpp"
    "${LIB_SOURCE_DIR}/imgui/imgui_widgets.cpp"
    "${LIB_SOURCE_DIR}/imgui/backends/imgui_impl_sdl2.cpp"
    "${LIB_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
)

set(PROGRAM_SOURCES
    "${SOURCE_DIR}/main.cpp"
    "${SOURCE_DIR}/Engine.cpp"
    "${SOURCE_DIR}/render/Renderer.cpp"
    "${SOURCE_DIR}/render/gl/GLProgram.cpp"
    "${SOURCE_DIR}/render/gl/GLShader.cpp"
    "${SOURCE_DIR}/render/gl/GLRenderObject.cpp"
    "${SOURCE_DIR}/render/objects/GLRenderObjectBackground.cpp"
    "${SOURCE_DIR}/render/objects/GLRenderObjectRainbowTriangle.cpp"
    "${SOURCE_DIR}/render/objects/GLRenderObjectImGui.cpp"
    "${SOURCE_DIR}/runtime/ThreadLooping.cpp"
    "${SOURCE_DIR}/sdl2/EventHandlerSDL2.cpp"
    "${SOURCE_DIR}/sdl2/TimerSDL2.cpp"
    "${SOURCE_DIR}/sdl2/WindowSDL2.cpp"
    "${SOURCE_DIR}/util/Fault.cpp"
    "${SOURCE_DIR}/util/Logger.cpp"
)


# Link libraries
find_package(cpptrace REQUIRED)
link_libraries("fmt" "cpptrace::cpptrace" "SDL2" "GL" "stb")


# Output
add_executable("zydeco" ${LIB_SOURCES} ${PROGRAM_SOURCES})
