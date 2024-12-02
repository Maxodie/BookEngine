@echo off
rem output directory
set target="Targets/%1"

rem generate cmake build files
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=%1 -DCMAKE_BUILD_TYPE=Debug -S./ -B %target%
