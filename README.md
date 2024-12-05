# Book Engine
This is an engine based on the book "3D Game Engine Development" by Franc Pouhela. The goal is to learn a new way of building a 3D game engine in cpp.

## How to run
There are multiple bat files if you want to build your environment with vs, or with Makefile and compile_commands.json (for neovim in my case) :
here is the bat file to generate the mingw makefile environment in debug mode :
```bat
@echo off
rem output directory
set target="Targets/%1"

rem generate cmake build files
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=%1 -DCMAKE_BUILD_TYPE=Debug -S./ -B %target%
```

Here is how I compile mingw32-make :
```bat
@echo off
rem output directory
set target="Targets/%1"

rem compile cmake build files
mingw32-make -C %target%
```
## Some parts differ from the book
I want the architecture of the book to remain very much the same. I've changed some parts to suit my writing conventions and environment preference.
So I use git submodules instead of connan, neovim instead of vs or vsc, and I used Glad instead of Glew for OpenGL.
