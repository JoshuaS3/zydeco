## Zydeco

Hobby project/experiment in C++, graphics programming, and world generation.

### Building

Run `./zydeco.sh` to compile, build, and run. Requires `CMake` and a `C++20`-capable compiler, as well as the dependencies below. Executable is outputted at `build/zydeco` in the project root directory.

Zydeco depends upon the following C/C++ libraries:

| Library | Purpose | Source |
| ------- | ------- | ------ |
| `fmt` | String formatting for debug output messages | `libfmt-dev` |
| `cpptrace` | Producing stack traces for fault output | [GitHub](https://github.com/jeremy-rifkin/cpptrace) |
| `SDL2` | Cross-platform solution for creating and managing windows, OpenGL contexts | `libsdl2-dev` |
