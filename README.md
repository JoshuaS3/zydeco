## Zydeco ([Fractal tag](https://joshstock.in/blog/opengl-fractal-explorer))

Hobby project/experiment in C++, graphics programming, and world generation.

### Building

Run `./zydeco.sh` to compile, build, and run. Requires `CMake` and a
`C++20`-capable compiler, as well as the dependencies below. Executable is
outputted at `build/zydeco` in the project root directory.

Zydeco depends upon the following C/C++ libraries:

| Library | Purpose | Source |
| ------- | ------- | ------ |
| `fmt` | String formatting for debug output messages | `libfmt-dev` |
| `cpptrace` | Producing stack traces for fault output | [GitHub](https://github.com/jeremy-rifkin/cpptrace) |
| `SDL2` | Cross-platform solution for creating and managing windows, OpenGL contexts | `libsdl2-dev` |
| `GL` | OpenGL | `libgl-dev` |
| `gl3w` | OpenGL loader with extensions enabled | [GitHub](https://github.com/skaslev/gl3w/blob/master/gl3w_gen.py) |
| `imgui` | Immediate-mode GUI, used for debug menus | [GitHub](https://github.com/ocornut/imgui) (docking branch) |

**Notes on installing dependencies:**

* `cpptrace` is included by `CMakeLists.txt` as a system-wide dependency. You can
either install it this way by the instructions in the linked repo, or remove
its use in `src/util/Fault.cpp` and the requirement in `CMakeLists.txt`.
* **`gl3w` should be run in a new directory `lib/gl3w` with `python3 gl3w_gen.py --ext`**
* Install imgui with `git clone --branch docking --single-branch --depth=1 https://github.com/ocornut/imgui.git` to `lib/gl3w`

Depending on how your package manager installed SDL2, there might be a
disparity for SDL2 `#include`s between imgui and this application. If this is
the case, you may need to manually update imgui or this source code to add or
remove "SDL2/" in `<SDL2/sdl_file_name.h>`, depending on where your package
manager installed things.


### Source Code

It's not as pretty as I made it look in the article. OpenGL abstractions in
`src/render`. Fractal application in `src/game/Mandelbrot.cpp`. Shaders in
`include/render/shaders`. If you're looking to try out new z-transforms, you'll
want to modify `include/render/shaders/fractal.cs.glsl`.

