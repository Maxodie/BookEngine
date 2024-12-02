@echo off
rem output directory
set target="Targets/%1"

rem generate cmake build files
cmake -S . -B %target% -DCMAKE_BUILD_TYPE=%1 rem  -DCMAKE_TOOLCHAIN_FILE="conanbuildinfo.cmake"
rem compile cmake build files
cmake --build %target% --config %1

PAUSE
