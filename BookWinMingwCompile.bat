@echo off
rem output directory
set target="Targets/%1"

rem compile cmake build files
mingw32-make -C %target%
